#include "lightsensor_dataprocessor.h"
#include "track_object.h"
#include <thread>

int main() {

  std::vector<std::thread> threads;

  UsbSerialLinux usb_serial_linux("/dev/ttyUSB0");
  std::shared_ptr<LightSensorDataControler> p_lsdc(new LightSensorDataControler(usb_serial_linux));
  std::shared_ptr<LightSensorDataProcessor> p_lsdp(new LightSensorDataProcessor(p_lsdc));
  TrackObject track_object(p_lsdc, p_lsdp);

  sleep(1);
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
