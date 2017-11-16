#pragma once
#include <track_object.h>

class EyeTracker : public TrackObject {
 private:
  Camera leftEyeCamera;
  Camera rightEyeCamera;
  Camera leftSceneCamera;
  Camera rightSceneCamera;

  LightRecevier lighthouseRecevier;
};

