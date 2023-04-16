#define ANALOG_PIN A2

float depth;  //unit:cm
int feet;
float ave;

void depthsensor_setup() {
  // analogReference(EXTERNAL);
  pinMode(ANALOG_PIN, INPUT); 
}

float getdepth() {
  ave = analogRead(ANALOG_PIN);
  depth = (0.8333*ave) - 120.8;
  feet = depth * 0.03280;

  if (feet < 0.9) {
    feet = 0.0;
  }

  return feet;
}