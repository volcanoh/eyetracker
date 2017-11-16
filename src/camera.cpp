#include "camera.h"

void Camera::SetId(int id) {
  this->id_ = id;
}
int Camera::GetId() {
  return id_;
}

bool Camera::Open() {
  if (!videoCapture_.open(id_)) {
    std::cerr << "open device camera: " << id_ << " failed!" << std::endl;
    return false;
  }
  else return true;
}
void Camera::Close() {
  videoCapture_.release();
}

bool Camera::IsOpened() {
  return videoCapture_.isOpened();
}

void Camera::GetCameraMatrix( cv::Mat &camMat ) {
  camMat = cameraMatrix_;
}
void Camera::SetCameraMatrix( const cv::Mat &camMat ) {
  cameraMatrix_ = camMat;
}
void Camera::GetImage( cv::Mat &image ) {
  if (!IsOpened()) {
    std::cerr << "camera " << id_ << "is not opened!" << std::endl;
    return;
  }
  videoCapture_ >> image;
}
void Camera::operator >>(cv::Mat &image) {
  GetImage(image);
}
Camera::Camera(int id) : id_(id) {
}

