#include <iostream>
#include <vector>
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

class LightHouse : public Object {
public:
  double getRotateSpeedX();
  void setRotateSpeedX(double x);

  double getRotateSpeedY();
  void setRotateSpeedY(double y);
private:
  double rotateSpeedX; // rotate speed of X
  double rotateSpeedY; // rotate speed of Y
}

class LightRecevier : public Object {
public:
  using LightSensorData = std::pair<int, int>;
  using LightSensorDataPacket = std::vector<LightSensorData>;
private:
  int lightSensorNumber;
  std::vector<cv::Point3d> lightSensorPoints;
};

class EyeTracker : public Object {
private:
  Camera leftEyeCamera;
  Camera rightEyeCamera;
  Camera leftSceneCamera;
  Camera rightSceneCamera;

  LightRecevier lighthouseRecevier;
};
