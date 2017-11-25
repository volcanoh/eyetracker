#pragma once
#include <opencv2/opencv.hpp>
#include <object.h>

class Camera : public Object {
public:
  Camera(int idx);
  Camera(Camera&);
  void SetId(int idx);
  int GetId();

  bool Open();
  void Close();
  bool IsOpened();

  void GetCameraMatrix(cv::Mat& camMat);
  void SetCameraMatrix(const cv::Mat& camMat);

  void GetImage(cv::Mat& image);
  Camera& operator >> (cv::Mat& image);

 private:
  int index_;

  cv::VideoCapture videoCapture_;
  cv::Mat cameraMatrix_;
};
