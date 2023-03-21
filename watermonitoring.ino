bool isTempStable = false;
bool isDepthStable = false;
bool allReadingsStable = false;

float raw_temp;

byte readingState = 0x01;
byte toSendState = 0x04;
byte sendingState = 0x05;
byte state = readingState;


void setup(void)
{
  Serial.begin(9600);
  ds18b20_setup();
  Serial.println("Reading state...");
}
void loop(void)
{
  getStable_ph();
  getStable_temp();
}
