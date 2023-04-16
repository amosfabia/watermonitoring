#define ANALOG_PIN A2

float depth, stableread, infeet;  //unit:cm
int feet;
float ave;

void depthsensor_setup() {
  // analogReference(EXTERNAL);
  pinMode(ANALOG_PIN, INPUT); 
}

float getdepth() {
  float ave = analogRead(A2);
  float depth = (0.8333*ave) - 120.8;
  depth = smooth(depth);
  
  if (depth < 0.9) {
    return 0.0;
  }
  
  stableread = depth * 0.01;
  infeet = stableread * 3.281;

  String feetstring = String(infeet,1);
  float finalfeet = feetstring.toFloat();
  return finalfeet;
}