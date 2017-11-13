#include "lightsensor_dataprocessor.h"
#include "track_object.h"
#include <thread>
#include <fstream>

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


  UsbSerialLinux usb_serial_linux("/dev/ttyUSB0");
  std::shared_ptr<LightSensorDataControler> p_lsdc(new LightSensorDataControler(usb_serial_linux));

  std::shared_ptr<LightSensorDataProcessor> p_lsdp(new LightSensorDataProcessor(p_lsdc));

  TrackObject track_object(p_lsdc, p_lsdp);

  std::vector<cv::Point3d> vertices;
  ReadPoints(vertices, "object_points.txt");
  track_object.SetVertices(vertices);

  sleep(1);
  std::vector<std::thread> threads;
  threads.push_back(std::thread([&]() {
        while(true) {
          if (p_lsdc->UpdateData()) {
            cout << "update data" << endl;
            usleep(1);
          }
        }
      }));

  threads.push_back(std::thread([&]() {
        track_object.StartTracking();
      }));

  threads.push_back(std::thread([&]() {
        sleep(10);
        track_object.Stop();
      }));
  for (auto& thread : threads) {
    thread.join();
  }
  usb_serial_linux.Close();
  return 0;
}
