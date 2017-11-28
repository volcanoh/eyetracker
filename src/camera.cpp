#include "camera.h"

void Camera::SetId(int idx) {
  this->index_ = idx;
}
int Camera::GetId() {
  return index_;
}

bool Camera::Open() {
  if (!videoCapture_.open(index_)) {
    std::cerr << "open device camera: " << index_ << " failed!" << std::endl;
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
    std::cerr << "camera " << index_ << "is not opened!" << std::endl;
    return;
  }
  videoCapture_ >> image;
}
Camera& Camera::operator >>(cv::Mat &image) {
  GetImage(image);
  return *this;
}
Camera::Camera(int idx) : index_(idx) {
}

Camera::Camera(Camera& c) {
  this->index_ = c.index_;
}
