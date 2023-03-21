
const int LONG_PRESS_TIME  = 1000; // 1000 milliseconds

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;


void resetreadORsendmsg() {
  // read the state of the switch/button:
  currentState = digitalRead(rstbtn);

  if (lastState == HIGH && currentState == LOW)       // button is pressed
    pressedTime = millis();
  else if (lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if ( pressDuration > LONG_PRESS_TIME )
      if (state == readingState) {
        Serial.println("start reading...");
        isTempStable = false;
        isPhStable = false;
        isDepthStable = false;
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
