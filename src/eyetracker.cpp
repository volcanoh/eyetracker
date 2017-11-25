#include <eyetracker.h>

EyeTracker::EyeTracker(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp, std::shared_ptr<Camera> lec, std::shared_ptr<Camera> rec, std::shared_ptr<Camera> lsc, std::shared_ptr<Camera> rsc) :
  TrackObject(p_lsdc, p_lsdp),
  object_manager_(ObjectManager::GetInstance()),
  p_left_eye_camera_(lec),
  p_right_eye_camera_(rec),
  p_left_scene_camera_(lsc),
  p_right_scene_camera_(rsc) {
    object_manager_.RegisterObject(this);
    object_manager_.RegisterObject(p_left_eye_camera_.get());
    object_manager_.RegisterObject(p_right_eye_camera_.get());
    object_manager_.RegisterObject(p_left_scene_camera_.get());
    object_manager_.RegisterObject(p_right_eye_camera_.get());
  }


void EyeTracker::SetPupilTrackingtALG(std::function<bool(const cv::Mat&, cv::RotatedRect&)> alg) {
      PupilTracking_ALG_ = alg;
    }

void EyeTracker::GetPupil(cv::RotatedRect& left_pupil, cv::RotatedRect& right_pupil) {
  left_pupil = left_pupil_;
  right_pupil = right_pupil_;
}
