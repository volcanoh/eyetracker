#include "lightsensor_datareader.h"
class LightSenrosDataInterpretor {
public:
  //double TimetickToAngle(unsigned short timetick);
  //unsigned short AngleToTimetick(double angle);
private:
  unsigned int index;
  unsigned short timetick_[36 * 2];

  double hit_map_[36 * 2]; // 36 pixels's x&y.
};

int main() {
  UsbSerialLinux usb_serial_linux("/dev/ttyUSB0");
  LightSenrosDataReader aaa(usb_serial_linux, 154);
  sleep(1);
  while(1) {
    if (aaa.Read())
      aaa.Print();
    usleep(100000);
  }
  usb_serial_linux.Close();
  return 0;
}
