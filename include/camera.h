#pragma once
#include <opencv2/opencv.hpp>
#include <object.h>

class Camera : public Object {
public:
  Camera(int id);
  void SetId(int id);
  int GetId();

  bool Open();
  void Close();
  bool IsOpened();

  void GetCameraMatrix(cv::Mat& camMat);
  void SetCameraMatrix(const cv::Mat& camMat);

  void GetImage(cv::Mat& image);
  void operator >> (cv::Mat& image);

 private:
  int id_;

  cv::VideoCapture videoCapture_;
  cv::Mat cameraMatrix_;
};
