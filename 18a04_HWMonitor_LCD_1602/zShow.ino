//-----------------------------------------------------------------------
void show() {
  if (bUpdateDisplay) {
    //    ulTimeout = millis();
    //    lcd.clear();
    lcd.setCursor(0, 0);
    printTime();

    lcd.setCursor(0, 1);
    if (phase < 4) printDate();
    else if (phase < 10) printTemperature();
    else printHumidity();

    lcd.setCursor(6, 0);
    printPU("CPU:", PCdata[0], PCdata[4]);

    lcd.setCursor(6, 1);
    printPU("FPU:", PCdata[1], PCdata[5]);

    //    lcd.scrollDisplayLeft();
    //    lcd.print(millis() - ulTimeout);
    bUpdateDisplay = 0;
  }
}
//-----------------------------------------------------------------------
void printTime() {
  char str[6] = "00:00";
  str[0] += tm.Hour / 10;
  str[1] += tm.Hour % 10;
  str[3] += tm.Minute / 10;
  str[4] += tm.Minute % 10;
  lcd.print(str);
}
//-----------------------------------------------------------------------
void printDate() {
  char str[6] = "00.00";
  str[0] += tm.Day / 10;
  str[1] += tm.Day % 10;
  str[3] += tm.Month / 10;
  str[4] += tm.Month % 10;
  lcd.print(str);
}
//-----------------------------------------------------------------------
void printTemperature() {
  lcd.write(7);
  lcd.print(fTemperature, 1);
}
//-----------------------------------------------------------------------
void printHumidity() {
  lcd.write('%');
  lcd.print(fHumidity, 1);
}
//-----------------------------------------------------------------------
void printPU(String name, int temperature, int duty) {
  lcd.print(name);
  if (temperature < 10) lcd.write('0');
  lcd.print(temperature);
  lcd.write(7);
  if (duty > 99) duty = 99;
  if (duty < 10) lcd.write('0');
  lcd.print(duty);
  lcd.write('%');
}
//-----------------------------------------------------------------------
void printFPU() {
  lcd.print("FPU:");
  if (PCdata[5] > 99) PCdata[5] = 99;
  lcd.print(PCdata[5]);
  lcd.write(7);
}
//-------  стартовый логотип AlexGyver ----------------------------------
byte char1[8] = {0b00011, 0b00110, 0b01110, 0b11111, 0b11011, 0b11001, 0b00000, 0b00000};
byte char2[8] = {0b10000, 0b00001, 0b00001, 0b00001, 0b00000, 0b10001, 0b11011, 0b11111};
byte char3[8] = {0b11100, 0b11000, 0b10001, 0b11011, 0b11111, 0b11100, 0b00000, 0b00000};
byte char4[8] = {0b00000, 0b00001, 0b00011, 0b00111, 0b01101, 0b00111, 0b00010, 0b00000};
byte char5[8] = {0b11111, 0b11111, 0b11011, 0b10001, 0b00000, 0b00000, 0b00000, 0b00000};
byte char6[8] = {0b00000, 0b10000, 0b11000, 0b11100, 0b11110, 0b11100, 0b01000, 0b00000};
//-------  значок градуса ----------------------------------
byte degree[8] = {0b01000, 0b10100, 0b01000, 0b00110, 0b01001, 0b01000, 0b01001, 0b00110};
//-----------------------------------------------------------------------
char logo0[4] = {1, 2, 3};
char logo1[4] = {4, 5, 6};
//-----------------------------------------------------------------------
void showLogo() {
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
  delay(4000);
  lcd.clear();                  // очистить дисплей
}
//-----------------------------------------------------------------------

