
void timeoutTick() {
  if ((millis() - timeout > 5000) && timeOut_flag) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("CONNECTION");
    lcd.setCursor(5, 1);
    lcd.print("FAILED");    
    timeOut_flag = 0;
    reDraw_flag = 1;
  }
}

