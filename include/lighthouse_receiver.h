#include <opencv2/opencv.hpp>
#include <object.h>
#include <lighthouse.h>
#include <ringbuffer.h>
class LightHouseReceiver : public Object {
public:
  void getRvecToLH(cv::Mat& rvec);
  void getTvecToLH(cv::Mat& tvec);
  bool start(); // start a thread.
  void run();   // receive serial data, and calculate R,t matrix.
  void stop();  // stop the thread.
private:
  int LightPointNum;
  std::vector<cv::Point3d> lightPoint3d;
  std::vector<cv::Point2d> hitMapPoint2d;
  cv::Mat rvecToLH;
  cv::Mat tvecToLH;
}
