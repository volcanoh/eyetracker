#include "lightsensor_datareader.h"

LightSensorDataReader::LightSensorDataReader(UsbSerial& usb_serial, int size) :
  usb_serial_(usb_serial),
  size_(size) {
  data_ = new char[size_];
  }
LightSensorDataReader::~LightSensorDataReader() {
  if (data_)
    delete[] data_;
}

int LightSensorDataReader::SearchBeginPos(char* buffer, const int size) {
  for (int i = 0; i < size - 1; ++i) {
    if (buffer[i] == '*' && buffer[i + 1] == '#')
      return i;
  }
  return -1;
}

bool LightSensorDataReader::CheckDataTail() {
  if (data_[size_ - 4] == '#' &&
      data_[size_ - 3] == '*' &&
      data_[size_ - 2] == '\r' &&
      data_[size_ - 1] == '\n')
    return true;
  return false;
}
bool LightSensorDataReader::UpdateData() {
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

bool LightSensorDataReader::GetLightSensorDataPacket(LightSensorDataPacket& lsdp) {
  if (!UpdateData()) return false;
  if (CheckDataTail()){
    memcpy(&lsdp, data_ + 2, sizeof(LightSensorDataPacket));
    return true;
  }
  return false;
}
