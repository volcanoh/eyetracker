#include "track_object.h"

TrackObject::TrackObject(std::shared_ptr<LightSensorDataControler> p_lsdc, std::shared_ptr<LightSensorDataProcessor> p_lsdp):
  p_lightsensor_data_controler_(p_lsdc),
  p_lightsensor_data_processor_(p_lsdp) {
  }

void TrackObject::StartTracking() {
  LightSensorCallback cb = [&](LightSensorDataPacket& lsd) {
    cout << lsd.index << endl;
    for (int i = 0; i < 36; ++i) {
      cout << lsd.timetick[2*i] << "," << lsd.timetick[2*i + 1] << "  ";
    } cout << endl << endl;
  };
  p_lightsensor_data_processor_->RegisterCallback(cb);
  p_lightsensor_data_processor_->LoopProcess();
}

void TrackObject::Stop() {
  p_lightsensor_data_processor_->Stop();
}
