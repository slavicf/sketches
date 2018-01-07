//-----------------------------------------------------------------------
String num2str(int val, char delim) {
  return String(val / 10) + String(val % 10) + delim;
}
//-----------------------------------------------------------------------
void show() {
  if (updateDisplay_flag) {
    
    time_t t = now();
    sTime = num2str(hour(t), ':') + num2str(minute(t), ' ');    //':') + num2str(second(t), ' ');
    sDate = num2str(day(t), '.') + num2str(month(t), ' ');    //'.') + num2str(year(t) - 2000, ' ');

    temp = dht.readTemperature();  // Read temperature as Celsius (the default)
    hum = dht.readHumidity();

    //  lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(sTime);
    lcd.print(temp, 1);  lcd.write(7);   // значок градуса
    lcd.setCursor(0, 1);
    lcd.print(sDate);
    lcd.print(hum, 1);  lcd.print('%');

    //  sCPUtemp = num2str(PCdata[0], ' ');
    //  sCPUload = num2str(PCdata[4] < 100 ? PCdata[0] : 99, ' ');

    lcd.setCursor(11, 0);  lcd.print(PCdata[0]);
    lcd.setCursor(11, 1);  lcd.print(PCdata[1]);

    //  lcd.scrollDisplayLeft();
  }
}

