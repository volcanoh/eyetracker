#include "lightsensor_dataprocessor.h"

LightSensorDataProcessor::LightSensorDataProcessor(std::shared_ptr<LightSensorDataControler> lsdc) :
  data_controler_(lsdc) {
}
void LightSensorDataProcessor::LoopProcess() {
  shallStop = false;
  while(true) {
    if (shallStop) break;
    if (data_controler_->GetLightSensorDataPacket(data_packet_))
      {
        callback_(data_packet_);
      }

  }
}

void LightSensorDataProcessor::Stop() {
  shallStop = true;
}


void LightSensorDataProcessor::RegisterCallback( LightSensorCallback cb ) {
  callback_ = cb;
}
