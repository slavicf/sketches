//-----------------------------------------------------------------------
void show() {
  if (bUpdateDisplay) {
    printLine1();
    printLine2();
    bUpdateDisplay = 0;
  }
}
//-----------------------------------------------------------------------
void printLine1() {
  lcd.setCursor(0, 0);
  if ((phase & 8) == 0) {
    printVal(tm.Hour, ':');
    printVal(tm.Minute, ' ');
  } else {
    lcd.print(fTemperature, 1);
    lcd.write(7);
  }
  lcd.setCursor(6, 0);
  printPC("C", tCPU, uCPU, uRAM);
}
//-----------------------------------------------------------------------
void printLine2() {
  lcd.setCursor(0, 1);
  if ((phase & 8) == 0) {
    printVal(tm.Day, '.');
    printVal(tm.Month, ' ');
  } else {
    lcd.print(fHumidity, 1);
    lcd.write('%');
  }
  lcd.setCursor(6, 1);
  printPC("G", tGPU, uGPU, uGRAM);
}
//-----------------------------------------------------------------------
void printVal(int val, char sign) {
  if (val > 99) val = 99;
  if (val < 10) lcd.write('0');
  lcd.print(val);
  lcd.write(sign);
}
//-----------------------------------------------------------------------
void printPC(String name, int temperature, int duty, int ram) {
  lcd.print(name);
  printVal(temperature, 7);
  printVal(duty, '%');
  printVal(ram, '%');
}
//-----------------------------------------------------------------------
byte char01[8] = {0b00011, 0b00110, 0b01110, 0b11111, 0b11011, 0b11001, 0b00000, 0b00000};  // стартовый
byte char02[8] = {0b10000, 0b00001, 0b00001, 0b00001, 0b00000, 0b10001, 0b11011, 0b11111};  // логотип
byte char03[8] = {0b11100, 0b11000, 0b10001, 0b11011, 0b11111, 0b11100, 0b00000, 0b00000};  // AlexGyver
byte char04[8] = {0b00000, 0b00001, 0b00011, 0b00111, 0b01101, 0b00111, 0b00010, 0b00000};  //
byte char05[8] = {0b11111, 0b11111, 0b11011, 0b10001, 0b00000, 0b00000, 0b00000, 0b00000};  //
byte char06[8] = {0b00000, 0b10000, 0b11000, 0b11100, 0b11110, 0b11100, 0b01000, 0b00000};  //
byte char07[8] = {0b01000, 0b10100, 0b01000, 0b00110, 0b01001, 0b01000, 0b01001, 0b00110};  // значок градуса
//-----------------------------------------------------------------------
char logo0[4] = {1, 2, 3};
char logo1[4] = {4, 5, 6};
//-----------------------------------------------------------------------
void showLogo() {
  lcd.createChar(1, char01);
  lcd.createChar(2, char02);
  lcd.createChar(3, char03);
  lcd.createChar(4, char04);
  lcd.createChar(5, char05);
  lcd.createChar(6, char06);
  lcd.createChar(7, char07);

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

