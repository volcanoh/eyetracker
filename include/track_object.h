#pragma once
#include <object.h>
#include "lightsensor_dataprocessor.h"
const double PI = 3.1415926;

class TrackObject : public Object {
 public:

  TrackObject(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp);

  TrackObject(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp, const std::vector<cv::Point3d>& vertices);
  void StartTracking();
  void Stop();
  void SetVertices(const std::vector<cv::Point3d>& vertices);

 private:
  cv::Matx31d rvecTrack;
  cv::Matx31d tvecTrack;

  std::vector<cv::Point3d> vertices_;
  std::shared_ptr<LightSensorDataControler> p_lightsensor_data_controler_;
  std::shared_ptr<LightSensorDataProcessor> p_lightsensor_data_processor_;
};
