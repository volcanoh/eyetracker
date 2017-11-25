#pragma once
#include <track_object.h>
#include <object_manager.h>
#include <camera.h>

class EyeTracker : public TrackObject {
 public:
  EyeTracker(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp, std::shared_ptr<Camera> lec, std::shared_ptr<Camera> rec, std::shared_ptr<Camera> lsc, std::shared_ptr<Camera> rsc);
 private:
  ObjectManager& object_manager_;
  std::shared_ptr<Camera> p_left_eye_camera_;
  std::shared_ptr<Camera> p_right_eye_camera_;
  std::shared_ptr<Camera> p_left_scene_camera_;
  std::shared_ptr<Camera> p_right_scene_camera_;
};
