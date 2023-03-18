bool isTempStable = false;
bool isPhStable = false;
bool isDepthStable = false;
bool allReadingsStable = false;
float raw_temp;
float raw_ph;

void setup(void)
{
  Serial.begin(9600);
  ds18b20_setup();
}
void loop(void)
{

  //  if (!isTempStable) {
  //    raw_temp = printTemperature();
  //    getStable_temp(raw_temp);
  //  }

  if (!isPhStable) {
    raw_ph = printpH();
    getStable_ph(raw_ph);
  }

  if (isTempStable && isPhStable) {
    allReadingsStable = true;
    Serial.println("readings are all stable");
    Serial.println("Send readings to gateway? press button to send");
  }

  sendWaterStatus(String(raw_temp), String(raw_ph));

}
