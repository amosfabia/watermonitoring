#define PHpin A0

float calibration_value = 21.34 + 1.33;
int phval = 0;
unsigned long int avgval;
int buffer_arr[10], temp;



float printpH() {
  float smoothed;
  for (int i = 0; i < 10; i++)
  {
    buffer_arr[i] = analogRead(PHpin);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buffer_arr[i] > buffer_arr[j])
      {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }
  avgval = 0;
  for (int i = 2; i < 8; i++)
    avgval += buffer_arr[i];
  float volt = (float)avgval * 5.0 / 1024 / 6;
  float ph_act = -5.70 * volt + calibration_value;
  smoothed = smooth(ph_act);
  return smoothed;
}

