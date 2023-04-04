//Parameters
const int numReadings   = 40;
int readings [numReadings];
int readIndex   = 0;
long total  = 0;
//Variables
int aisVal  = 0;

float smooth(float numIn) { /* function smooth */
  ////Perform average on sensor readings
  float average;
  // subtract the last reading:
  total = total - readings[readIndex];
  // read the sensor:
  readings[readIndex] = numIn;
  // add value to total:
  total = total + readings[readIndex];
  // handle index
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  // calculate the average:
  average = total / numReadings;
  return average;
}