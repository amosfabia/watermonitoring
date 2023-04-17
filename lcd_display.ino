#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t check[8] = { 0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0 };

void lcd_setup() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Water Monitor");
  lcd.createChar(5, check);
}

void navRead_display() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp ");
  lcd.setCursor(6, 0);
  lcd.print("pH ");
  lcd.setCursor(10, 0);
  lcd.print("depth ");
  if (isDepthStable) stableChecksymbol(15, 0);
  if (isPhStable) stableChecksymbol(8, 0);
  if (isTempStable) stableChecksymbol(4, 0);
  temp_display();
  ph_display();
  depth_display();
}

void navSend_display() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Send to LoRa");
  // longPressSend();
}

void longPressSend(){
  lcd.setCursor(0, 1);
  lcd.print("LongPress-send");
}

void temp_display() {

  lcd.setCursor(0, 1);
  lcd.print(temp_lastReading, 1);
  lcd.print(" ");
}

void ph_display() {

  lcd.setCursor(6, 1);
  lcd.print(ph_lastReading, 1);
  lcd.print(" ");
}

void depth_display() {

  lcd.setCursor(10, 1);
  lcd.print(depth_lastReading, 1);
  lcd.print(" ");
}

void countReset_display() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(1, 1);
  lcd.print("reset Reading");
  delay(2000);
  lcd.setCursor(1, 1);
  lcd.print("               ");
}

void sending_display() {
  lcd.setCursor(0, 1);
  lcd.print("Sending...      ");
}

void sendingFailed_display() {
  lcd.setCursor(0, 1);
  lcd.print("Sending Failed   ");
  delay(2000);
  // longPressSend();
}

void sendingSuccess_display() {
  lcd.setCursor(0, 1);
  lcd.print("Send Success! ");
  delay(5000);
  // longPressSend();
}

void stableChecksymbol(byte col, byte row) {
  lcd.setCursor(col, row);
  lcd.write(5);
}

void navigate_display() {
  if (changeState) {

    switch (state) {

      case readingState:
        navRead_display();
        changeState = false;
        break;

      case toSendState:
        navSend_display();
        changeState = false;
        break;

        // case sendingState:
        //   sending_display();
        //   changeState = false;
        //   break;

      case sendSuccessState:
        sendingSuccess_display();
        changeState = false;
        Serial.println("---received---");
        state = toSleepState;
        break;
    }
  }
}