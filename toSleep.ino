#include "LowPower.h"

void can_I_sleep() {
  
  if (state == toSleepState) {
    Serial.println("tulog na me...");
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }

}

