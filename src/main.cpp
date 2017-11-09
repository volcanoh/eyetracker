#include "lightsensor_dataprocessor.h"
#include <thread>

int main() {

  std::vector<std::thread> threads;

  UsbSerialLinux usb_serial_linux("/dev/ttyUSB0");

  std::shared_ptr<LightSensorDataControler> p_lsdc(new LightSensorDataControler(usb_serial_linux));

  LightSensorDataProcessor lsdp(p_lsdc);

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
        LightSensorCallback cb = [&](LightSensorDataPacket& lsd) {
          cout << lsd.index << endl;
          for (int i = 0; i < 36; ++i) {
            cout << lsd.timetick[2*i] << "," << lsd.timetick[2*i + 1] << "  ";
          } cout << endl << endl;
        };
        lsdp.RegisterCallback(cb);
        lsdp.LoopProcess();
      }));

  threads.push_back(std::thread([&]() {
        sleep(10);
        lsdp.Stop();
      }));
  for (auto& thread : threads) {
    thread.join();
  }
  usb_serial_linux.Close();
  return 0;
}
