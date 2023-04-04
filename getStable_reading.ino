bool isTempStable = false;
bool isDepthStable = false;
bool isPhStable = false;

unsigned long temp_lastReadTime = 0;
unsigned long ph_lastReadTime = 0;
unsigned long depth_lastReadTime = 0;

const int readInterval = 5000;  //wait 5 seconds for readings to change

float temp_lastReading;
float ph_lastReading;
float depth_lastReading;


//----------------------------------------------------------------

void getStable_temp() {
  if (isTempStable) {
    return;
  }

  float recentReading = printTemperature();


  if (recentReading != temp_lastReading) {
    temp_lastReadTime = millis();
  } 
  
  else if ((millis() - temp_lastReadTime) > 1000) {
    Serial.print("temp: ");
    Serial.println(recentReading);
    Serial.println("stable temperature reading");
    isTempStable = true;
  }

  temp_lastReading = recentReading;
}

//-----------------------------------------------------

void getStable_ph() {

  if (isPhStable ||  !isDepthStable) {
    return;
  }


  float ph_recentReading = printpH();
  Serial.println(ph_recentReading);

  if (ph_recentReading != ph_lastReading) {
    ph_lastReadTime = millis();
  }

  if ((millis() - ph_lastReadTime) > readInterval) {
    Serial.print("ph: ");
    Serial.println(ph_recentReading);
    Serial.println("stable ph reading");
    isPhStable = true;
  }

  ph_lastReading = ph_recentReading;
}

void getStable_depth() {

  if (isDepthStable) {
    return;
  }

  float depth_recentReading = getdepth();
  Serial.println(depth_recentReading);

  if (depth_recentReading != depth_lastReading) {
    depth_lastReadTime = millis();
  }

  if ((millis() - depth_lastReadTime) > readInterval) {
    Serial.print("depth: ");
    Serial.println(depth_recentReading);
    Serial.println("stable depth reading");
    isDepthStable = true;
    analogReference(DEFAULT);
  }

  depth_lastReading = depth_recentReading;
}

//----------------------------------------------------------------

void startmonitoring() {
  if (state == readingState) {
    getStable_ph();
    getStable_temp();
    getStable_depth();
    if (isTempStable && isPhStable && isDepthStable) {
      state = finishreadState;
      Serial.println("Finished Reading.");
    }
  }
}
