#include "track_object.h"

TrackObject::TrackObject(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp):
  p_lightsensor_data_controler_(p_lsdc),
  p_lightsensor_data_processor_(p_lsdp) {
  }

TrackObject::TrackObject(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp, const std::vector<cv::Point3d>& vertices) :
  vertices_(vertices),
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
  LightSensorCallback cb = [&](LightSensorDataPacket& lsd) {
    cout << lsd.index << endl;
    std::vector<cv::Point2d> image_points;
    std::vector<cv::Point3d> object_points;

    for (int i = 0; i < 32; ++i) {
      if (lsd.timetick[2*i] == 0 || lsd.timetick[2*i+1] == 0)
        continue;
      // cout << lsd.timetick[2*i] << "," << lsd.timetick[2*i+1] << "  ";
      double angle_x = TimetickToAngle(lsd.timetick[2*i]);
      double angle_y = TimetickToAngle(lsd.timetick[2*i + 1]);

      auto img_pt = ProjectionPoint(angle_x, angle_y);
      auto obj_pt = vertices_[i];
      image_points.push_back(img_pt);
      object_points.push_back(obj_pt);
    } cout << endl << endl;
    //cv::solvePnP(object_points, image_points, cv::Matx33d::eye(), cv::Mat(), rvecTrack, tvecTrack, false, cv::SOLVEPNP_ITERATIVE);
    cv::solvePnP(object_points, image_points, cv::Matx33d::eye(), cv::Mat(), rvecTrack, tvecTrack, false, cv::SOLVEPNP_EPNP);
    //cv::solvePnPRansac(object_points, image_points, cv::Matx33d::eye(), cv::Mat(), rvecTrack, tvecTrack, false, 100, 8.0, 100);
    cout << "tvec:\n " << tvecTrack << endl << "rvec:\n" << rvecTrack << endl << endl;
  };
  p_lightsensor_data_processor_->RegisterCallback(cb);
  p_lightsensor_data_processor_->LoopProcess();
}

void TrackObject::StopTracking() {
  p_lightsensor_data_processor_->Stop();
}

void TrackObject::SetVertices(const  std::vector<cv::Point3d>& vertices ) {
  vertices_ = vertices;
}
