bool isTempStable = false;
bool isDepthStable = false;
bool isPhStable = false;

unsigned long temp_lastReadTime = 0;
unsigned long ph_lastReadTime = 0;
unsigned long depth_lastReadTime = 0;

const int readInterval = 2000;  //wait 2 seconds for readings to change

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
    stableChecksymbol(4, 0);
    temp_display();
  }
  temp_lastReading = recentReading;
}

//-----------------------------------------------------

void getStable_ph() {

  if (isPhStable) {
    return;
  }


  float ph_recentReading = String(printpH(), 1).toFloat();
  // Serial.println(ph_recentReading);

  if (ph_recentReading != ph_lastReading) {
    ph_lastReadTime = millis();
  }

  if ((millis() - ph_lastReadTime) > readInterval) {
    Serial.print("ph: ");
    Serial.println(ph_recentReading);
    Serial.println("stable ph reading");
    stableChecksymbol(8, 0);
    isPhStable = true;
    analogReference(EXTERNAL);
    ph_display();
  }
  ph_lastReading = ph_recentReading;
}

//---------------------------------------------------------------------

void getStable_depth() {

  if (isDepthStable || !isPhStable) {
    return;
  }

  float depth_recentReading = getdepth();
  // Serial.println(depth_recentReading);

  if (depth_recentReading != depth_lastReading) {
    depth_lastReadTime = millis();
  }

  if ((millis() - depth_lastReadTime) > 1000) {
    Serial.print("depth: ");
    Serial.println(depth_recentReading);
    Serial.println("stable depth reading");
    stableChecksymbol(15, 0);
    isDepthStable = true;
    depth_display();
  }
  depth_display();
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
