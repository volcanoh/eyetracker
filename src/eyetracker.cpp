#include <eyetracker.h>

EyeTracker::EyeTracker(
  UsbSerial& usb_serial,
  std::vector<cv::Point3d> vertices, std::string left_pupil_config_file, std::string right_pupil_config_file, size_t packet_size, size_t serial_data_size, int lec_id, int rec_id, int lsc_id, int rsc_id) 
  :
    TrackObject(usb_serial, vertices, packet_size, serial_data_size),
    object_manager_(ObjectManager::GetInstance()),
    left_pupil_tracker_(left_pupil_config_file),
    right_pupil_tracker_(right_pupil_config_file){
      object_manager_.RegisterObject(this);
      object_manager_.RegisterObject(&left_eye_camera_);
      object_manager_.RegisterObject(&right_eye_camera_);
      object_manager_.RegisterObject(&left_scene_camera_);
      object_manager_.RegisterObject(&right_eye_camera_);

      if (lec_id >= 0) left_eye_camera_ = Camera(lec_id);
      if (rec_id >= 0) right_eye_camera_ = Camera(rec_id);
      if (lsc_id >= 0) left_scene_camera_ = Camera(lsc_id);
      if (rsc_id >= 0) right_scene_camera_ = Camera(rsc_id);
    }


/*EyeTracker::EyeTracker(UsbSerial& usb_serial, std::vector<cv::Point3d> vertices, std::string left_pupil_config_file, std::string right_pupil_config_file, size_t packet_size, size_t serial_data_size, std::string lec_fn, std::string rec_fn, std::string lsc_fn, std::string rsc_fn)*/
//:
//TrackObject(usb_serial, vertices, packet_size, serial_data_size),
//object_manager_(ObjectManager::GetInstance()),
//left_pupil_tracker_(left_pupil_config_file),
//right_pupil_tracker_(right_pupil_config_file){
//object_manager_.RegisterObject(this);
//object_manager_.RegisterObject(&left_eye_camera_);
//object_manager_.RegisterObject(&right_eye_camera_);
//object_manager_.RegisterObject(&left_scene_camera_);
//object_manager_.RegisterObject(&right_eye_camera_);

//if (lec_fn != "") left_eye_camera_ = Camera(lec_fn);
//if (rec_fn != "") right_eye_camera_ = Camera(rec_fn);
//if (lsc_fn != "") left_scene_camera_ = Camera(lsc_fn);
//if (rsc_fn != "") right_scene_camera_ = Camera(rsc_fn);
//}

bool EyeTracker::SetCamera(CameraTypes type, int device) {
  switch (type) {
    case kLeftEyeCamera:
      return left_eye_camera_.open(device);
    case kRightEyeCamera:
      return right_eye_camera_.open(device);
    case kLeftSceneCamera:
      return left_scene_camera_.open(device);
    case kRightSceneCamera:
      return right_scene_camera_.open(device);
    case kUnknownCamera:
      return false;
    default:
      return false;
  }
}

bool EyeTracker::SetCamera(CameraTypes type, std::string fn) {
  switch (type) {
    case kLeftEyeCamera:
      return left_eye_camera_.open(fn);
    case kRightEyeCamera:
      return right_eye_camera_.open(fn);
    case kLeftSceneCamera:
      return left_scene_camera_.open(fn);
    case kRightSceneCamera:
      return right_scene_camera_.open(fn);
    case kUnknownCamera:
      return false;
    default:
      return false;
  }
}



void EyeTracker::GetPupil(cv::RotatedRect& left_pupil, cv::RotatedRect& right_pupil) {
  std::lock_guard<std::mutex> lock(mtx_);
  left_pupil = left_pupil_;
  right_pupil = right_pupil_;
}
void EyeTracker::StartPupilTracking() {
  shall_stop_ = false;
  thd_ = std::thread([&]() {
    cv::Mat left_eye_image, right_eye_image;
    cv::RotatedRect left_ellipse, right_ellipse;
    while(!shall_stop_) {
      left_eye_camera_ >> left_eye_image;
      right_eye_camera_ >> right_eye_image;

      if (left_pupil_tracker_.FindPupilEllipse(left_eye_image, left_ellipse)) {
        std::lock_guard<std::mutex> lock(mtx_);
        left_pupil_ = left_ellipse;
        //std::cout << left_pupil_.center << std::endl;
      }
      if (right_pupil_tracker_.FindPupilEllipse(right_eye_image, right_ellipse)) {
        std::lock_guard<std::mutex> lock(mtx_);
        right_pupil_ = right_ellipse;
        //std::cout << right_pupil_.center << std::endl;
      }
    }
  });
  //thd_.join();
}

void EyeTracker::StopPupilTracking() {
  shall_stop_ = false;
}

void EyeTracker::Join() {
  TrackObject::Join();
  if (thd_.joinable())
    thd_.join();
}
