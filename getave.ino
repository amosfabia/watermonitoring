//Parameters
const int numReadings   = 50;
float readings [numReadings];
int readIndex   = 0;
float total  = 0;

//Variables

float smooth(float numIn) { /* function smooth */
  ////Perform average on sensor readings
  // subtract the last reading:
  float average;
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