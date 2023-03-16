
void setup(void)
{
  Serial.begin(9600);
  ds18b20_setup();
}
void loop(void)
{
 
  printTemperature(); // Use a simple function to print out the data
}
