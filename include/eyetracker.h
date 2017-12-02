#pragma once
#include <track_object.h>
#include <object_manager.h>
#include <camera.h>
#include <functional>

class EyeTracker : public TrackObject {
  public:
    EyeTracker(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp);

void SetPupilTrackingtALG(std::function<bool(const cv::Mat&, cv::RotatedRect&)> alg);

void GetPupil(cv::RotatedRect& left_pupil, cv::RotatedRect& right_pupil);

void PupilTracking() {
  if (!PupilTracking_ALG_) return;
  cv::Mat left_eye_image, right_eye_image;
  left_eye_camera_ >> left_eye_image;
  right_eye_camera_ >> right_eye_image;
  PupilTracking_ALG_(left_eye_image, left_pupil_);
  PupilTracking_ALG_(right_eye_image, right_pupil_);
}

  private:
    ObjectManager& object_manager_;
    Camera left_eye_camera_;
    Camera right_eye_camera_;
    Camera left_scene_camera_;
    Camera right_scene_camera_;
    
    cv::RotatedRect left_pupil_;
    cv::RotatedRect right_pupil_;

    std::function<bool(const cv::Mat&, cv::RotatedRect&)> PupilTracking_ALG_;
};

