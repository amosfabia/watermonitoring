#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 8

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

DeviceAddress insideThermometer = { 0x28, 0x18, 0xBF, 0x79, 0x97, 0x07, 0x03, 0x21 };

float tempC;
float tempReadings;

void ds18b20_setup() {

  Serial.println("Dallas Temperature IC Control Library Demo");

  // report parasite power requirements
  Serial.print("Parasite power is: ");

  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);
}



// function to print the temperature for a device
float printTemperature()
{
  sensors.requestTemperatures(); // Send the command to get temperatures

  float tempC = sensors.getTempC(insideThermometer);
  if (tempC == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
  }
  else {
    return tempC;
  }

}
