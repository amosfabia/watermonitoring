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
float ph_recentReading;
float ph_lastave, ph_recentave;

//----------------------------------------------------------------

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

//-----------------------------------------------------

void getStable_ph() {
  
  if (isPhStable) {
    return;
  }
  
  ph_recentReading = printpH();
  
  ph_recentave = (ph_recentReading + ph_lastReading)/2;
  
  Serial.print("ph: ");
  Serial.println(ph_recentave);
  
  if (ph_recentave != ph_lastave) {
    ph_lastReadTime = millis();
  }
  
  if ((millis() - ph_lastReadTime) > 200) {
    Serial.println("stable ph reading");
    isPhStable = true;
  }
  ph_lastave = ph_recentave;
  ph_lastReading = ph_recentReading;
}

//----------------------------------------------------------------

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
