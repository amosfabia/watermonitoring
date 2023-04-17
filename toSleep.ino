#include "LowPower.h"

void can_I_sleep() {

  if (state == toSleepState) {
    Serial.println("tulog na me...");
    sleepNaKo_display();
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);

    lcd_wakeup();
    readAgain();
  }
}


void readAgain() {
  Serial.println("start reading...");
  isTempStable = false;
  isPhStable = false;
  isDepthStable = false;
  state = readingState;
  analogReference(DEFAULT);
  navRead_display();
}