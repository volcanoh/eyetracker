#include "track_object.h"

TrackObject::TrackObject(UsbSerial& usb_serial, const std::vector<cv::Point3d>& vertices, int packet_size) :
  Consumer<LightSensorDataPacket>(data_packet_),
  Productor<LightSensorDataPacket>(data_packet_),
  vertices_(vertices),
  usb_serial_(usb_serial) {
     data_packet_ = new RingBuffer<LightSensorDataPacket>(packet_size);
  }

bool TrackObject::Product() {
  auto  SearchBeginPos = [](char* buffer, const int size) -> int{
    for (int i = 0; i < size - 1; ++i) {
      if (buffer[i] == '*' && buffer[i + 1] == '#')
        return i;
    }
    return -1;
  };
  auto CheckDataTail = [&]() {
    if (data_[kSerialDataSize - 4] == '#' &&
        data_[kSerialDataSize - 3] == '*' &&
        data_[kSerialDataSize - 2] == '\r' &&
        data_[kSerialDataSize - 1] == '\n')
      return true;
    return false;
  };

  char buffer[kSerialDataSize];
  usb_serial_.Read(buffer, kSerialDataSize);
  int begin_pos = SearchBeginPos(buffer, kSerialDataSize);
  if (begin_pos == -1) {
    return false;
  }
  else {
    memcpy(data_, buffer + begin_pos, kSerialDataSize - begin_pos);
  }
  int ret = usb_serial_.Read(data_ + kSerialDataSize - begin_pos, begin_pos); // read the rest data.
  if (!ret) return ret;

  if (CheckDataTail()) {
    LightSensorDataPacket lsdp;
    memcpy(&lsdp, data_ + 2, sizeof(LightSensorDataPacket));
    if (data_packet_->Write(&lsdp, 1) == 1)
      return true;
    else {
      cerr << "ringbuffer is no free space!" << endl;
      usleep(1);
      return false;
    }
    return true;
  }
  return false;
}

bool TrackObject::Consume() {
  static auto TimetickToAngle = [](unsigned short timetick)->double {
    return timetick / 8333.33 * PI - PI / 2;
  };
  static auto AngleToTimetick = [](double angle)->unsigned short{
    return (angle + PI / 2) * 8333.33 / PI;
  };

  static auto ProjectionPoint = [](double angle_x, double angle_y)->cv::Point2d {
    double x = tan(angle_x);
    double y = tan(angle_y);
    return cv::Point2d(x, y);
  };
  //auto SolverPnP = [&](){
  LightSensorDataPacket light_sensor_data_packet;
  bool ret = data_packet_->Read(&light_sensor_data_packet, 1);
  if (!ret) {
    usleep(1);
    return ret;
  } 
  cout << light_sensor_data_packet.index << endl;
  std::vector<cv::Point2d> image_points;
  std::vector<cv::Point3d> object_points;

  for (int i = 0; i < 32; ++i) {
    if (light_sensor_data_packet.timetick[2*i] == 0 || light_sensor_data_packet.timetick[2*i+1] == 0)
      continue;
    // cout << lsd.timetick[2*i] << "," << lsd.timetick[2*i+1] << "  ";
    double angle_x = TimetickToAngle(light_sensor_data_packet.timetick[2*i]);
    double angle_y = TimetickToAngle(light_sensor_data_packet.timetick[2*i + 1]);

    auto img_pt = ProjectionPoint(angle_x, angle_y);
    auto obj_pt = vertices_[i];
    image_points.push_back(img_pt);
    object_points.push_back(obj_pt);
  } cout << endl << endl;
  //cv::solvePnP(object_points, image_points, cv::Matx33d::eye(), cv::Mat(), rvecTrack, tvecTrack, false, cv::SOLVEPNP_ITERATIVE);
  ret = cv::solvePnP(object_points, image_points, cv::Matx33d::eye(), cv::Mat(), rvecTrack, tvecTrack, false, cv::SOLVEPNP_EPNP);
  //cv::solvePnPRansac(object_points, image_points, cv::Matx33d::eye(), cv::Mat(), rvecTrack, tvecTrack, false, 100, 8.0, 100);
  cout << "tvec:\n " << tvecTrack << endl << "rvec:\n" << rvecTrack << endl << endl;
  return ret;
  //};
}

void TrackObject::Start() {
  thread_.push_back(std::thread([&]() {
    Consumer<LightSensorDataPacket>::Start();
  }));
  thread_.push_back(std::thread([&]() {
    Productor<LightSensorDataPacket>::Start();
  }));
  for (auto & it : thread_) it.join();
}

void TrackObject::Stop() {
  Consumer<LightSensorDataPacket>::Stop();
  Productor<LightSensorDataPacket>::Stop();
}
