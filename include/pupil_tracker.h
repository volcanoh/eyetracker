#pragma once
#include <opencv2/opencv.hpp>
#include<pupiltracker/PupilTracker.h>
#include<pupiltracker/utils.h>
#include<pupiltracker/cvx.h>

class PupilTracker {
  public:
    PupilTracker(std::string cfg);
    bool FindPupilEllipse(const cv::Mat& src, cv::RotatedRect& ellipse);
  private:
    pupiltracker::ConfigFile parser_;
    pupiltracker::TrackerParams params_;
    pupiltracker::tracker_log log_;
    pupiltracker::findPupilEllipse_out out;
};


