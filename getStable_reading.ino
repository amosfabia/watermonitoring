unsigned long lastReadTime = 0;
int readInterval = 5000;          //wait 5 seconds for readings to change

void waitForStableRead(){
  
}

if (recentReading != lastReading) {
    // reset the debouncing timer
    lastReadTime = millis();
  }

  if ((millis() - lastReadTime) > readInterval) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    
  }

  lastReading = recentReading;
