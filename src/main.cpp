#include <lightsensor_dataprocessor.h>
#include <track_object.h>
#include <object_manager.h>
#include <eyetracker.h>
#include <thread>
#include <fstream>

void SleepMs(int time) {
#ifdef __unix
  usleep(1000*time);
#elif defined _WIN32
  Sleep(time);
#endif
}


bool ReadPoints(std::vector<cv::Point3d>& pts, std::string file) {
  int nums = 0;
  ifstream fin(file, fstream::in);
  if (!fin.is_open()) return false;
  fin >> nums;
  double x = 0, y = 0, z = 0;
  for (int i = 0; i < nums; ++i) {
    fin >> x >> y >> z;
    pts.push_back(cv::Point3d(x, y, z));
  }
  return true;
}

int main() {
#ifdef __unix
  UsbSerialLinux usb_serial("/dev/ttyUSB0");
#elif defined _WIN32
  UsbSerialWin usb_serial("COM3");
#endif
  if (!usb_serial.IsOpened()) return -1;
  std::shared_ptr<LightSensorDataControler> p_lsdc(new LightSensorDataControler(usb_serial));

  std::shared_ptr<LightSensorDataProcessor> p_lsdp(new LightSensorDataProcessor(p_lsdc));

  int left_eye_camera_id = 0;
  int right_eye_camera_id = 1;
  int left_scene_camera_id = 2;
  int right_scene_camera_id = 3;
  std::shared_ptr<Camera> p_left_eye_camera(new Camera(left_eye_camera_id));
  std::shared_ptr<Camera> p_right_eye_camera(new Camera(right_eye_camera_id));
  std::shared_ptr<Camera> p_left_scene_camera(new Camera(left_scene_camera_id));
  std::shared_ptr<Camera> p_right_scene_camera(new Camera(right_scene_camera_id));

  // ObjectManager test
  EyeTracker eye_tracker(p_lsdc, p_lsdp, p_left_eye_camera, p_right_eye_camera, p_left_scene_camera, p_right_scene_camera);

  std::vector<cv::Point3d> vertices;
  string object_points_file = "object_points.txt";
  if (!ReadPoints(vertices, object_points_file)) {
    cout << "Can not find file: " << object_points_file << endl;
    return -1;
  }
  eye_tracker.SetVertices(vertices);

  SleepMs(1);
  std::vector<std::thread> threads;
  threads.push_back(std::thread([&]() {
    while(true) {
      if (p_lsdc->UpdateData()) {
        cout << "update data" << endl;
        SleepMs(1);
      }
    }
  }));

  threads.push_back(std::thread([&]() {
    eye_tracker.StartTracking();
  }));

  threads.push_back(std::thread([&]() {
    SleepMs(10000);
    eye_tracker.StopTracking();
  }));
  for (auto& thread : threads) {
    thread.join();
  }
  usb_serial.Close();
  return 0;
}
