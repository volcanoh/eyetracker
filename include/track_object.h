#pragma once
#include <object.h>

class TrackObject : public Object {
 private:
  cv::Mat rvecTrack;
  cv::Mat tvecTrack;

  int vertexNumber;
  std::vector<cv::Point3d> vertices;
}
