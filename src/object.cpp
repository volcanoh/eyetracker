#include "object.h"

void Object::setTvec( const cv::Mat &tv ) {
  tvec = tv;
}
void Object::getTvec( cv::Mat &tv ) {
  tv = tvec;
}
void Object::setRvec( const cv::Mat &rv ) {
  rvec = rv;
}
void Object::getRvec( cv::Mat &rv ) {
  rv = rvec;
}
