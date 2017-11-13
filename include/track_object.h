#pragma once
#include <object.h>
#include "lightsensor_dataprocessor.h"

class TrackObject : public Object {
 public:
  TrackObject(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp);
  void StartTracking();
  void Stop();
 private:
  cv::Mat rvecTrack;
  cv::Mat tvecTrack;

 private:
  int vertexNumber;
  std::vector<cv::Point3d> vertices;
  std::shared_ptr<LightSensorDataControler> p_lightsensor_data_controler_;
  std::shared_ptr<LightSensorDataProcessor> p_lightsensor_data_processor_;
};

