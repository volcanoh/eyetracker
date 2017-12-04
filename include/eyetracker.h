#pragma once
#include <track_object.h>
#include <object_manager.h>
#include <camera.h>
#include <functional>
#include <pupil_tracker.h>

class EyeTracker : public TrackObject {
  public:
    enum CameraTypes {
      kUnknownCamera = -1,
      kLeftEyeCamera,
      kRightEyeCamera,
      kLeftSceneCamera,
      kRightSceneCamera
    };

    EyeTracker(UsbSerial& usb_serial, std::vector<cv::Point3d> vertices, std::string left_pupil_config_file, std::string right_pupil_config_file, size_t packet_size = 10, size_t serial_data_size = 154, int lec_id = -1, int rec_id = -1, int lsc_id = -1, int rsc_id = -1);
    
    //EyeTracker(UsbSerial& usb_serial, std::vector<cv::Point3d> vertices, std::string left_pupil_config_file, std::string right_pupil_config_file, size_t packet_size = 10, size_t serial_data_size = 154, std::string lec_fn = "", std::string rec_fn = "", std::string lsc_fn = "", std::string rsc_fn = "");
    
    bool SetCamera(CameraTypes type, int device);
    bool SetCamera(CameraTypes type, std::string fn);

    void GetPupil(cv::RotatedRect& left_pupil, cv::RotatedRect& right_pupil);

    void StartPupilTracking();
    void StopPupilTracking();
    virtual void Join();

  private:
    ObjectManager& object_manager_;
    Camera left_eye_camera_;
    Camera right_eye_camera_;
    Camera left_scene_camera_;
    Camera right_scene_camera_;

    cv::RotatedRect left_pupil_;
    cv::RotatedRect right_pupil_;

    PupilTracker left_pupil_tracker_;
    PupilTracker right_pupil_tracker_;

    bool shall_stop_; 
    std::mutex mtx_;
    std::thread thd_;
};

