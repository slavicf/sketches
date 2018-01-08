//-----------------------------------------------------------------------
void setup(void) {

  lcd.init();                   // initialize the lcd
  lcd.backlight();
  lcd.clear();                  // очистить дисплей
  showLogo();

  Timer1.initialize(timerPeriod);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(interrupt);  // attaches callback() as a timer overflow interrupt

  Serial.begin(9600);
  dht.begin();

  setSyncProvider(RTC.get);   // the function to get the time from the RTC
//  setSyncInterval(3600);
//  if (timeStatus() != timeSet)
//    Serial.println("Unable to sync with the RTC");
//  else
//    Serial.println("RTC has set the system time");
}
//-----------------------------------------------------------------------
void loop(void) {
  readData();
  show();
}
//-----------------------------------------------------------------------
void interrupt() {
  phase = (phase < 16) ? phase + 1 : 0;
  bReadTime = 1;
  bUpdateDisplay = 1;
  if (phase % 4 == 0) bReadDHT22 = 1;
}
//-----------------------------------------------------------------------

