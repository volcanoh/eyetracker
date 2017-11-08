#include "lightsensor_datareader.h"

LightSensorDataReader::LightSensorDataReader(UsbSerial& usb_serial, int size) :
  usb_serial_(usb_serial),
  size_(size) {
  data_ = new char[size_];
  }
LightSensorDataReader::~LightSensorDataReader() {
  delete[] data_;
}
int LightSensorDataReader::SearchBeginPos(char* buffer, const int size) {
  for (int i = 0; i < size - 1; ++i) {
    if (buffer[i] == '*' && buffer[i + 1] == '#')
      return i;
  }
  return -1;
}

bool LightSensorDataReader::Read() {
  char* buffer = new char[size_];
  usb_serial_.Read(buffer, size_);
  int begin_pos = SearchBeginPos(buffer, size_);
  if (begin_pos == -1) {
    delete[] buffer;
    return false;
  }
  else {
    memcpy(data_, buffer + begin_pos, size_ - begin_pos);
  }
  usb_serial_.Read(data_ + size_ - begin_pos, begin_pos); // read the rest data.
  delete[] buffer;
  return true;
}


