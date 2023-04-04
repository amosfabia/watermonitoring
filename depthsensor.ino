#define ANALOG_PIN A2

float depth;  //unit:mA
float ave;

void depthsensor_setup() {
  analogReference(EXTERNAL);
  pinMode(ANALOG_PIN, INPUT);
}

float getdepth() {
  ave = analogRead(ANALOG_PIN);
  depth = (0.8333 * ave) - 120.8;

  if (depth < 0.9) {
    depth = 0.0;
  }

  return smooth(depth);
}