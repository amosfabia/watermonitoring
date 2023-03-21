unsigned long temp_lastReadTime = 0;
unsigned long ph_lastReadTime = 0;
unsigned long depth_lastReadTime = 0;

const int readInterval = 1000;          //wait 5 seconds for readings to change
float temp_lastReading;
float ph_lastReading;
float depth_lastReading;

bool isPhStable = false;

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
  
  if (recentReading != ph_lastReading) {
    ph_lastReadTime = millis();
  }

  else if ((millis() - ph_lastReadTime) > readInterval) {
    Serial.println("stable ph reading");
    isPhStable = true;
  }

  ph_lastReading = recentReading;
}
