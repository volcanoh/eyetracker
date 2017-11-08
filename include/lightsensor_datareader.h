#pragma once
#include <iostream>
using namespace std;
#include "serial.h"
struct LightSensorDataPacket {
  unsigned int index;
  unsigned short timetick[36 * 2];
};
class LightSensorDataReader {
 public:
  LightSensorDataReader(UsbSerial& usb_serial, int size);
  ~LightSensorDataReader();
  bool GetLightSensorDataPacket(LightSensorDataPacket& lsdp);
 private:
  int SearchBeginPos(char* buffer, const int size);
  bool CheckDataTail();
  bool UpdateData();

  UsbSerial& usb_serial_;
  int size_;
  char* data_;
};
