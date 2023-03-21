
void ISR_sendRead() {
  if (state == readingState) {
    state = toSendState;             // pause counting
    Serial.println("to send state");
  }
  else if (state == toSendState) {
    state = readingState;
    Serial.println("counting state");
  }

}

void my_interrupt_handler() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    ISR_sendRead(); 
  }
  last_interrupt_time = interrupt_time;
}
