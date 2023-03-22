#define csPin  10         // LoRa radio chip select
#define resetPin  -1       // LoRa radio reset
#define irqPin  2         // change for your board; must be a hardware interrupt pin

#include <SPI.h>              // include libraries
#include <LoRa.h>

byte localAddress = 0xAA;     // address of this device
byte destination = 0xFF;      // destination to send to

unsigned long lastSendTime = 0;        // last send time
int interval = 3000;                   // send msg every 5 seconds

String acknowledge = "monitor";        // symbol or word to check from esp8266 reply(callback)
byte maxSentMsg = 3;                  // continue to send until max limit reached,then show "failed to send"

String msg = " ";

void LoRaSetup() {
   LoRa.setPins(10, -1, 2);
  if (!LoRa.begin(433E6)) {                       // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                                 // if failed, do nothing
  }
  Serial.println("LoRa init succeeded.");

  LoRa.setSpreadingFactor(12);
  LoRa.setSyncWord(0x55);

  LoRa.onReceive(onReceive);
  LoRa.onTxDone(onTxDone);
  LoRa_rxMode();
}

void onTxDone() {
  LoRa_rxMode();
  Serial.print("sent status: ");
  Serial.println(msg);
  numSentMsg += 1;
}

void LoRa_txMode(){
  LoRa.idle();                          // set standby mode
  LoRa.disableInvertIQ();                // active invert I and Q signals
}

void LoRa_rxMode(){
  LoRa.enableInvertIQ();               // normal mode
  LoRa.receive();                       // set receive mode
}

void sendWaterStatus() {
  if (state == sendingState) {                            //send continuously until esp8266 replied
    if (millis() - lastSendTime > interval) {    //send every interval seconds
      msg = String(temp_lastReading)+'$'+ph_lastReading;
      sendMessage(msg);
      lastSendTime = millis();                    // timestamp the message

    }

    if (numSentMsg >= maxSentMsg) {
      state = toSendState;                           //used to stop sending
      Serial.println("sending failed, long press to resend");
      numSentMsg = 0;
    }
    
  }
}


void sendMessage(String outgoing) {
  LoRa_txMode();
  LoRa.beginPacket();                            // start packet
  LoRa.write(destination);                       // add destination address
  LoRa.write(localAddress);                      // add sender address
  LoRa.write(outgoing.length());                 // add payload length
  LoRa.print(outgoing);                          // add payload
  LoRa.endPacket(true);                              // finish packet and send it                          // increment message ID
}


void onReceive(int packetSize) {        

  // read packet header bytes:
  int receiver = LoRa.read();                  // receiver address
  byte sender = LoRa.read();                    // sender address
  byte incomingLength = LoRa.read();            // incoming msg length

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                                    // skip rest of function
  }

  // if the receiver isn't this device or broadcast,
  if (receiver != localAddress && receiver != 0xFF) {
    Serial.println("This message is not for me.");
    return;                                    // skip rest of function
  }

  if (incoming == acknowledge) {
    state = toSendState;                      //stop sending after received callback
    Serial.print("sent success");
    numSentMsg = 0;
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(receiver, HEX));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();
}
