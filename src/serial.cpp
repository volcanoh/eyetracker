#include "serial.h"
#include <iostream>
#include <vector>
using namespace std;

#ifdef __unix

UsbSerialLinux::UsbSerialLinux() {
  device_ = "";
  fd_ = 0;
}

UsbSerialLinux::UsbSerialLinux(string device) {
  device_ = "";
  fd_ = 0;
  Open(device);
}

int UsbSerialLinux::Open(string device) {
  if (IsOpened()) {
    std::cout << "device is opened" << std::endl;
    return -1;
  }
  device_ = device;
  fd_ = open(device_.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd_ == -1) {
    cerr << "Can't Open Serial Port" << endl;
    return -1;
  }
  struct termios options;
  if (tcgetattr(fd_, &options) != 0)
    cout << "SetupSerial 1" << endl;;
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN] = 0;
	if (tcsetattr(fd_, TCSANOW, &options) != 0)
    cout << "SetupSerial 3" << endl;
  return fd_;
}

bool UsbSerialLinux::Read(char *buf, int length) {
  if (!IsOpened()) {
    cout << "error read serial: is not opened" << endl;
    return false;
  }
  char* buf_tmp = buf;
  int bytes_remain = length;
  int bytes_read = 0;
  int count = 0;
  do {
    bytes_read = read(fd_, buf_tmp, bytes_remain);
    if (bytes_read > 0) {
      count = 0;
      buf_tmp += bytes_read;
      bytes_remain -= bytes_read;
    }
    else {
      count++;
      if (count > 500) {
        cout << "error read serial: timeout" << endl;
        return false;
      }
    }
  } while(bytes_remain > 0);
  return true;
}

bool UsbSerialLinux::Close() {
  if (IsOpened())
    return close(fd_);
}

#endif
