#include "track_object.h"

TrackObject::TrackObject(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp):
  p_lightsensor_data_controler_(p_lsdc),
  p_lightsensor_data_processor_(p_lsdp) {
  }

void TrackObject::StartTracking() {

  auto TimetickToAngle = [](unsigned short timetick)->double {
    return timetick / 8333.33 * PI - PI / 2;
  };
  auto AngleToTimetick = [](double angle)->unsigned short{
    return (angle + PI / 2) * 8333.33 / PI;
  };

  auto ProjectionPoint = [](double angle_x, double angle_y)->cv::Point2d {
    double x = tan(angle_x);
    double y = tan(angle_y);
    return cv::Point2d(x, y);
  };
  std::vector<cv::Point2d> image_points;
  std::vector<cv::Point3d> object_points;

  LightSensorCallback cb = [&](LightSensorDataPacket& lsd) {
    cout << lsd.index << endl;
    for (int i = 0; i < 36; ++i) {
      if (lsd.timetick[2*i] == 0 || lsd.timetick[2*i+1] == 0)
        continue;
      double angle_x = TimetickToAngle(lsd.timetick[2*i]);
      double angle_y = TimetickToAngle(lsd.timetick[2*i + 1]);

      auto img_pt = ProjectionPoint(angle_x, angle_y);
      auto obj_pt = vertices_[i];
      image_points.push_back(img_pt);
      object_points.push_back(obj_pt);
    } cout << endl << endl;
    cv::solvePnP(object_points, image_points, cv::Matx33d::eye(), cv::Mat(), rvecTrack, tvecTrack, true, cv::SOLVEPNP_ITERATIVE);
  };
  p_lightsensor_data_processor_->RegisterCallback(cb);
  p_lightsensor_data_processor_->LoopProcess();
}

void TrackObject::Stop() {
  p_lightsensor_data_processor_->Stop();
}

void TrackObject::SetVertices(const  std::vector<cv::Point3d>& vertices ) {
  vertices_ = vertices;
}
