bool isTempStable = false;


void setup(void)
{
  Serial.begin(9600);
  ds18b20_setup();
}
void loop(void)
{

 if(!isTempStable){
  float temp = printTemperature();
  getStable_temp(temp);
 }

}
