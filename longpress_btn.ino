
const int LONG_PRESS_TIME  = 1000; // 1000 milliseconds


bool lastState = HIGH;
bool currentState;  
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;


void resetreadORsendmsg() {

  currentState = digitalRead(rstbtn);

  if (lastState == HIGH && currentState == LOW)       // button is pressed
    pressedTime = millis();
  else if (lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;


    if ( pressDuration > LONG_PRESS_TIME )
      if (state == finishreadState || state == readingState) {
        Serial.println("start reading...");
        isTempStable = false;
        isPhStable = false;
        isDepthStable = false;
        state = readingState;
        analogReference(EXTERNAL);
      }
      else if (state == toSendState) {
        Serial.println("Sending readings...");
        state = sendingState;
        numSentMsg = 0;                   // reset tracking of msgs sent
      }
  }

  // save the the last state
  lastState = currentState;
}
