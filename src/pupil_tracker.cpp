//#include <pupil_tracker.h>
//PupilTracker::PupilTracker(std::string cfg) {
//  parser_.read(cfg);
//  params_.Radius_Min = parser_.get<int>("Radius_Min");
//  params_.Radius_Max = parser_.get<int>("Radius_Max");
//
//  params_.CannyBlur = parser_.get<int>("CannyBlue");
//  params_.CannyThreshold1 = parser_.get<int>("CannyThreshold1");
//  params_.CannyThreshold2 = parser_.get<int>("CannyThreshold2");
//  params_.StarburstPoints = parser_.get<int>("StarburstPoints");
//
//  params_.PercentageInliers = parser_.get<int>("PercentageInliers");
//  params_.InlierIterations = parser_.get<int>("InlierIterations");
//  params_.ImageAwareSupport = parser_.get<bool>("ImageAwareSupport");
//  params_.EarlyTerminationPercentage = parser_.get<int>("EarlyTerminationPercentage");
//  params_.EarlyRejection = parser_.get<int>("EarlyRejection");
//  params_.Seed = parser_.get<int>("Seed");
//}
//
//bool PupilTracker::FindPupilEllipse(const cv::Mat& src, cv::RotatedRect& ellipse) {
//  bool ret = pupiltracker::findPupilEllipse(params_, src, out, log_);
//  if (ret) ellipse = out.elPupil;
//  return ret;
//}
