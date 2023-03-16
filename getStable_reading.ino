unsigned long temp_lastReadTime = 0;
unsigned long ph_lastReadTime = 0;
unsigned long depth_lastReadTime = 0;

const int readInterval = 5000;          //wait 5 seconds for readings to change
float temp_lastReading;
float ph_lastReading;
float depth_lastReading;


void getStable_temp(float reading) {
  
  float recentReading = reading;
  
  if (recentReading != temp_lastReading) {
    temp_lastReadTime = millis();
  }
  else if ((millis() - temp_lastReadTime) > readInterval) {
    Serial.println("stable reading");
    isTempStable = true;
  }

  temp_lastReading = recentReading;
}