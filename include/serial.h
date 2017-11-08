#pragma once
#include <iostream>
using namespace std;
#include <string.h>     // string function definitions
#ifdef __unix
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <termios.h>    // POSIX terminal control definitions
#endif


class UsbSerial {
public:
  virtual int Open(string device) = 0;
  virtual bool Read(char* buf, int length) = 0;
  virtual bool Close() = 0;
  virtual bool IsOpened() = 0;
  string device_;
};

#ifdef __unix
class UsbSerialLinux :public UsbSerial {
public:
  UsbSerialLinux(string device);
  UsbSerialLinux();
  int Open(string device);
  bool Read(char* buf, int length);
  bool Close();

  bool IsOpened() {
    return fd_ > 0 ? true : false;
  }
private:
  int fd_;
};
#endif
