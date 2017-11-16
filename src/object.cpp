#include "object.h"

void Object::setTvec( const cv::Matx31d &tv ) {
  tvec = tv;
}
void Object::getTvec( cv::Matx31d &tv ) {
  tv = tvec;
}
void Object::setRvec( const cv::Matx31d &rv ) {
  rvec = rv;
}
void Object::getRvec( cv::Matx31d &rv ) {
  rv = rvec;
}
