#include "lightsensor_datareader.h"
int main() {
  UsbSerialLinux usb_serial_linux("/dev/ttyUSB0");
  LightSensorDataReader aaa(usb_serial_linux, 154);
  sleep(1);
  LightSensorDataPacket lsdp;
  while(1) {
    aaa.GetLightSensorDataPacket(lsdp);
    cout << lsdp.index << endl;
    for (int i = 0; i < 36; ++i) {
      cout << lsdp.timetick[2*i] << "," << lsdp.timetick[2*i + 1] << "  ";
    }cout << endl << endl;
  }
  usb_serial_linux.Close();
  return 0;
}
