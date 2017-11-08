#pragma once
#include <iostream>
using namespace std;
#include "serial.h"
#include "ringbuffer.h"

const int kSerialDataSize = 154;

struct LightSensorDataPacket {
  unsigned int index;
  unsigned short timetick[36 * 2];
};
class LightSensorDataReader {
 public:
  LightSensorDataReader(UsbSerial& usb_serial, int size);
  ~LightSensorDataReader();
  bool UpdateData();
  bool GetLightSensorDataPacket(LightSensorDataPacket& lsdp);
 private:
  int SearchBeginPos(char* buffer, const int size);
  bool CheckDataTail();

  UsbSerial& usb_serial_;
  char data_[kSerialDataSize];
  RingBuffer<LightSensorDataPacket> lightsensor_datapacket_;
};
