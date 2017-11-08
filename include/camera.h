#pragma once
#include <opencv2/opencv.hpp>
#include <object.h>

class Camera : public Object {
public:
  Camera(int id);
  void setId(int id);
  int getId();

  bool open();
  void close();
  bool isOpened();

  void getCameraMatrix(cv::Mat& camMat);
  void setCameraMatrix(const cv::Mat& camMat);

  void getImage(cv::Mat& image);
  Camera& operator >> (cv::Mat& image);

 private:
  int id;

  cv::VideoCapture videoCapture;
  cv::Mat cameraMatrix;
};
