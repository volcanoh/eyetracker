#pragma once
#include <opencv2/opencv.hpp>

class Object {
public:

  void getRvec(cv::Mat& rv);
  void setRvec(const cv::Mat& rv);

  void getTvec(cv::Mat& tv);
  void setTvec(const cv::Mat& tv);

private:
  cv::Mat rvec;
  cv::Mat tvec;
};

