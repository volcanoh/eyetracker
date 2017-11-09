#pragma once
#include "lightsensor_datacontroler.h"
#include <functional>
#include <memory> // shared_ptr
#include <atomic>

using LightSensorCallback = std::function<void(LightSensorDataPacket&)>;

class LightSensorDataProcessor {
 public:
  LightSensorDataProcessor(std::shared_ptr<LightSensorDataControler> lsdc);
  void LoopProcess();
  void Stop();
  void RegisterCallback(LightSensorCallback cb);

 private:
  inline double TimetickToAngle(unsigned short timetick) {
    return 0;
  }
  inline unsigned short AngleToTimetick(double angle) {
    return 0;
  }

  LightSensorCallback callback_;
  LightSensorDataPacket data_packet_;
  std::atomic_bool shallStop;
  std::shared_ptr<LightSensorDataControler> data_controler_;
};

