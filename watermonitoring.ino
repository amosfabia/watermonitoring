#define sendCountbttn 3
#define rstbtn 7

byte numSentMsg = 0;

const byte readingState = 0x01;
const byte toSendState = 0x04;
const byte sendingState = 0x05;
byte state = readingState;


void setup(void)
{
  attachInterrupt(digitalPinToInterrupt(sendCountbttn), my_interrupt_handler, FALLING);
  Serial.begin(9600);
  Serial.println("Water monitoring");

  ds18b20_setup();
  Serial.println("Reading state...");
}
void loop(void) {

  startmonitoring();
  sendWaterStatus();
  resetreadORsendmsg();
}
