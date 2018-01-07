
void show_logo() {
  lcd.createChar(0, logo0);
  lcd.createChar(1, logo1);
  lcd.createChar(2, logo2);
  lcd.createChar(3, logo3);
  lcd.createChar(4, logo4);
  lcd.createChar(5, logo5);
  lcd.setCursor(0, 0);
  lcd.printByte(0);
  lcd.printByte(1);
  lcd.printByte(2);
  lcd.setCursor(0, 1);
  lcd.printByte(3);
  lcd.printByte(4);
  lcd.printByte(5);
  lcd.setCursor(4, 0);
  lcd.print("AlexGyver");
  lcd.setCursor(4, 1);
  lcd.print("Technologies");
}
void show_logo2() {
  lcd.setCursor(1, 0);
  lcd.print("modified by");
  lcd.setCursor(5, 1);
  lcd.print("klykov.net");
}

