
//void ISR_sendCount() {
//  if (state == countingState) {
//    state = toSendState;             // pause counting
//    numSentMsg = 0;                   // reset tracking of msgs sent
//    Serial.println("to send state");
//  }
//  else if (state == toSendState) {
//    state = countingState;
//    Serial.println("counting state");
//  }
//
//}
//
//void my_interrupt_handler() {
//  static unsigned long last_interrupt_time = 0;
//  unsigned long interrupt_time = millis();
//  // If interrupts come faster than 200ms, assume it's a bounce and ignore
//  if (interrupt_time - last_interrupt_time > 200) 
//  {
//    ISR_sendCount(); 
//  }
//  last_interrupt_time = interrupt_time;
//}
