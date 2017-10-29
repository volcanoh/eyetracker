#include "camera.h"

void Camera::setId(int id) {
  this->id = id;
}
int Camera::getId() {
  return id;
}

bool Camera::open() {
  if (!videoCapture.open(id)) {
    std::cerr << "open device camera: " << id << " failed!" << std::endl;
    return false;
  }
  else return true;
}
void Camera::close() {
  videoCapture.release();
}

bool Camera::isOpened() {
  return videoCapture.isOpened();
}

void Camera::getCameraMatrix( cv::Mat &camMat ) {
  camMat = cameraMatrix;
}
void Camera::setCameraMatrix( const cv::Mat &camMat ) {
  cameraMatrix = camMat;
}
void Camera::getImage( cv::Mat &image ) {
  if (!isOpened()) {
    std::cerr << "camera " << id << "is not opened!" << std::endl;
    return;
  }
  videoCapture >> image;
}
Camera& Camera::operator>>(cv::Mat &image) {
  getImage(image);
  return *this;
}
Camera::Camera(int id) : id(id) {
}

