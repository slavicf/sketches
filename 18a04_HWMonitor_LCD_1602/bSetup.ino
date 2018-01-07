//-----------------------------------------------------------------------
void setup(void) {
  Serial.begin(9600);
  dht.begin();
  lcd.init();                   // initialize the lcd
  lcd.backlight();
  lcd.clear();                  // очистить дисплей

  lcd.createChar(1, char1);
  lcd.createChar(2, char2);
  lcd.createChar(3, char3);
  lcd.createChar(4, char4);
  lcd.createChar(5, char5);
  lcd.createChar(6, char6);
  lcd.createChar(7, degree);

  lcd.setCursor(0, 0);
  lcd.print(logo0);
  lcd.print(" AlexGyver");
  lcd.setCursor(0, 1);
  lcd.print(logo1);
  lcd.print(" Technologies");
  delay(5000);
  lcd.clear();                  // очистить дисплей

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  //  if (timeStatus() != timeSet)
  //    Serial.println("Unable to sync with the RTC");
  //  else
  //    Serial.println("RTC has set the system time");
}

