#pragma once
#include <opencv2/opencv.hpp>

class Object {
public:

  Object();

  void getRvec(cv::Matx31d& rv);
  void setRvec(const cv::Matx31d& rv);

  void getTvec(cv::Matx31d& tv);
  void setTvec(const cv::Matx31d& tv);

  void SetId(int);
  int GetId();

private:
  cv::Matx31d rvec;
  cv::Matx31d tvec;

  int id_;
};

