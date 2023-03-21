bool isTempStable = false;
bool isDepthStable = false;
bool isPhStable = false;

unsigned long temp_lastReadTime = 0;
unsigned long ph_lastReadTime = 0;
unsigned long depth_lastReadTime = 0;

const int readInterval = 1000;          //wait 5 seconds for readings to change
float temp_lastReading;
float ph_lastReading;
float depth_lastReading;

void getStable_temp() {
   if (isTempStable) {
    return;
  }

  float recentReading = printTemperature();
  Serial.print("temp: ");
  Serial.println(recentReading);

  if (recentReading != temp_lastReading) {
    temp_lastReadTime = millis();
  }
  else if ((millis() - temp_lastReadTime) > readInterval) {
    Serial.println("stable temperature reading");
    isTempStable = true;
  }

  temp_lastReading = recentReading;
}

void getStable_ph() {
  
  if (isPhStable) {
    return;
  }
  
  float recentReading = printpH();
  
  Serial.print("ph: ");
  Serial.println(recentReading);
  
  if (abs(recentReading - ph_lastReading) > 0.01) {
    ph_lastReadTime = millis();
  }

  else if ((millis() - ph_lastReadTime) > readInterval) {
    Serial.println("stable ph reading");
    isPhStable = true;
  }

  ph_lastReading = recentReading;
}


void startmonitoring(){
  if (state == readingState) {
    getStable_ph();
    getStable_temp();
    if(isTempStable && isPhStable){
      state = finishreadState;
      Serial.println("Finished Reading.");
    }
  }
}
