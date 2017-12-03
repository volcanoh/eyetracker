#pragma once
#include <object.h>
#include <consumer.h>
#include <productor.h>
#include <serial.h>
#include <ringbuffer.h>
#include <thread>
const double PI = 3.1415926;

const int kSerialDataSize = 154;

struct LightSensorDataPacket {
  unsigned int index;
  unsigned short timetick[36 * 2];
};

class TrackObject : public Object, public Consumer<LightSensorDataPacket>, public Productor<LightSensorDataPacket> {
  public:

    TrackObject(UsbSerial& usb_serial, const std::vector<cv::Point3d>& vertices, int packet_size = 10);

    virtual void Start();
    virtual void Stop();
    virtual bool Product();
    virtual bool Consume();

    void SetVertices(const std::vector<cv::Point3d>& vertices);

  private:

    char data_[kSerialDataSize];

    cv::Matx31d rvecTrack;
    cv::Matx31d tvecTrack;

    std::vector<cv::Point3d> vertices_;

    UsbSerial& usb_serial_;
    RingBuffer<LightSensorDataPacket>* data_packet_;
    std::vector<std::thread> thread_;
};

