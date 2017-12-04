#include <eyetracker.h>

EyeTracker::EyeTracker(
    UsbSerial& usb_serial,
    std::vector<cv::Point3d> vertices, size_t packet_size, size_t serial_data_size, int lec_id, int rec_id, int lsc_id, int rsc_id) 
  :
  TrackObject(usb_serial, vertices, packet_size, serial_data_size),
  object_manager_(ObjectManager::GetInstance()) {
    object_manager_.RegisterObject(this);
    object_manager_.RegisterObject(&left_eye_camera_);
    object_manager_.RegisterObject(&right_eye_camera_);
    object_manager_.RegisterObject(&left_scene_camera_);
    object_manager_.RegisterObject(&right_eye_camera_);

    if (lec_id >= 0) left_eye_camera_ = Camera(lec_id);
    if (lec_id >= 0) right_eye_camera_ = Camera(rec_id);
    if (lec_id >= 0) left_scene_camera_ = Camera(lsc_id);
    if (lec_id >= 0) right_scene_camera_ = Camera(rsc_id);
}


void EyeTracker::SetPupilTrackingtALG(std::function<bool(const cv::Mat&, cv::RotatedRect&)> alg) {
      PupilTracking_ALG_ = alg;
    }

void EyeTracker::GetPupil(cv::RotatedRect& left_pupil, cv::RotatedRect& right_pupil) {
  left_pupil = left_pupil_;
  right_pupil = right_pupil_;
}
