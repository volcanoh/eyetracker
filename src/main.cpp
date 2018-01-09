#include <iostream>

#include <pcl/visualization/pcl_visualizer.h>

#include <track_object.h>
#include <object_manager.h>
#include <eyetracker.h>
#include <thread>
#include <fstream>

#include "viewer.h"
#include "surface.h"

void test_pcl() {
  Viewer v("PCL Viewer");
  boost::shared_ptr<Surface> s(new Surface("surface"));

  s->FillSurface();
  v.AddVisualable(s);
  v.AddCoordinateSystem(1.0, 0, 0, 0, "reference");
  v.InitCameraParameters();
  v.SetRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, s->Name());
  v.Spin();
}


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

int main(int argc, char* argv[]) {
  if (argc < 4) {
    cout << "usage: \n\b ./demo object_points_file left_pupil_config right_pupil_config\n";
    return -1;
  } 
#ifdef __unix
  UsbSerialLinux usb_serial("/dev/ttyUSB0");
#elif defined _WIN32
  UsbSerialWin usb_serial("COM3");
#endif
  if (!usb_serial.IsOpened()) return -1;

  std::vector<cv::Point3d> vertices;
  string object_points_file(argv[1]);
  if (!ReadPoints(vertices, object_points_file)) {
    cout << "Can not find file: " << object_points_file << endl;
    return -1;
  }
  // ObjectManager test
  std::string left_pupil_config = argv[2];
  std::string right_pupil_config = argv[3];
  EyeTracker eye_tracker(usb_serial, vertices, left_pupil_config, right_pupil_config);
  eye_tracker.SetCamera(EyeTracker::CameraTypes::kLeftEyeCamera, "1.avi");
  eye_tracker.SetCamera(EyeTracker::CameraTypes::kRightEyeCamera, "2.avi");
  cout << "Starting lighthouse tracking" << endl;
  eye_tracker.Start();
  cout << "Starting pupil tracking" << endl;
  eye_tracker.StartPupilTracking();

  test_pcl();

  eye_tracker.Join();

  usb_serial.Close();
  return 0;
}



