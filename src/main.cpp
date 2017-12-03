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

  std::vector<cv::Point3d> vertices;
  string object_points_file = "object_points.txt";
  if (!ReadPoints(vertices, object_points_file)) {
    cout << "Can not find file: " << object_points_file << endl;
    return -1;
  }
  // ObjectManager test
  cout << "Initializing EyeTracker" << endl;
  EyeTracker eye_tracker(usb_serial, vertices);
  cout << "EyeTracker initialized" << endl;
  eye_tracker.Start();

  usb_serial.Close();
  return 0;
}
