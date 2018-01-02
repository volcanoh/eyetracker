#pragma once
#include <opencv2/opencv.hpp>
#include "object.hpp"

class Camera : public Object, public cv::VideoCapture {
public:
  Camera();
  Camera(const std::string& filename);
  Camera(int device);

  void GetCameraMatrix(cv::Mat& camMat);
  void SetCameraMatrix(const cv::Mat& camMat);

 private:
  cv::Mat cameraMatrix_;
};
