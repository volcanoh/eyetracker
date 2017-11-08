#pragma once
#include <iostream>
using namespace std;
#include "serial.h"
class LightSenrosDataReader {
 public:
  LightSenrosDataReader(UsbSerial& usb_serial, int size);
  ~LightSenrosDataReader();
  int SearchBeginPos(char* buffer, const int size);
  bool Read();
  void Print() {
    for (int i = 0; i < size_; ++ i) {
      cout << hex <<(short) data_[i];
    } cout << endl;
  }
 private:
  UsbSerial& usb_serial_;
  int size_;
  char* data_;
};
