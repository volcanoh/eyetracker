#include <eyetracker.h>

EyeTracker::EyeTracker(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp) :
  TrackObject(p_lsdc, p_lsdp),
  object_manager_(ObjectManager::GetInstance()) {
    object_manager_.RegisterObject(this);
    object_manager_.RegisterObject(left_eye_camera_);
    object_manager_.RegisterObject(right_eye_camera_);
    object_manager_.RegisterObject(left_scene_camera_);
    object_manager_.RegisterObject(right_eye_camera_);
  }


void EyeTracker::SetPupilTrackingtALG(std::function<bool(const cv::Mat&, cv::RotatedRect&)> alg) {
      PupilTracking_ALG_ = alg;
    }

void EyeTracker::GetPupil(cv::RotatedRect& left_pupil, cv::RotatedRect& right_pupil) {
  left_pupil = left_pupil_;
  right_pupil = right_pupil_;
}
