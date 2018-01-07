
void draw_stats_11() {
  lcd.setCursor(4, 0); lcd.print(PCdata[0]); lcd.write(223);
  lcd.setCursor(13, 0); lcd.print(PCdata[4]);
  if (PCdata[4] < 10) perc = "% ";
  else if (PCdata[4] < 100) perc = "%";
  else perc = "";  lcd.print(perc);
  lcd.setCursor(4, 1); lcd.print(PCdata[1]); lcd.write(223);
  lcd.setCursor(13, 1); lcd.print(PCdata[5]);
  if (PCdata[5] < 10) perc = "% ";
  else if (PCdata[5] < 100) perc = "%";
  else perc = "";  lcd.print(perc);

  for (int i = 0; i < 2; i++) {
    byte line = ceil(PCdata[lines[i]] / 16);
    lcd.setCursor(7, i);
    if (line == 0) lcd.printByte(1)
      else lcd.printByte(4);
    for (int n = 1; n < 5; n++) {
      if (n < line) lcd.printByte(4);
      if (n >= line) lcd.printByte(2);
    }
    if (line == 6) lcd.printByte(4)
      else lcd.printByte(3);
  }
}

void draw_stats_12() {
  lcd.setCursor(13, 0); lcd.print(PCdata[7]);
  if (PCdata[7] < 10) perc = "% ";
  else if (PCdata[7] < 100) perc = "%";
  else perc = "";  lcd.print(perc);
  lcd.setCursor(13, 1); lcd.print(PCdata[6]);
  if (PCdata[6] < 10) perc = "% ";
  else if (PCdata[6] < 100) perc = "%";
  else perc = "";  lcd.print(perc);

  for (int i = 0; i < 2; i++) {
    byte line = ceil(PCdata[lines[i + 2]] / 16);
    lcd.setCursor(7, i);
    if (line == 0) lcd.printByte(1)
      else lcd.printByte(4);
    for (int n = 1; n < 5; n++) {
      if (n < line) lcd.printByte(4);
      if (n >= line) lcd.printByte(2);
    }
    if (line == 6) lcd.printByte(4)
      else lcd.printByte(3);
  }
}

void draw_stats_21() {
  lcd.setCursor(13, 0); lcd.print(duty);
  if ((duty) < 10) perc = "% ";
  else if ((duty) < 100) perc = "%";
  else perc = "";  lcd.print(perc);

  lcd.setCursor(3, 1); lcd.print(temp1); lcd.write(223);
  lcd.setCursor(11, 1); lcd.print(temp2); lcd.write(223);

  byte line = ceil(duty / 16);
  lcd.setCursor(6, 0);
  if (line == 0) lcd.printByte(1)
    else lcd.printByte(4);
  for (int n = 1; n < 5; n++) {
    if (n < line) lcd.printByte(4);
    if (n >= line) lcd.printByte(2);
  }
  if (line == 6) lcd.printByte(4)
    else lcd.printByte(3);
}
void draw_stats_22() {
  lcd.setCursor(2, 0); lcd.print(PCdata[2]); lcd.write(223);
  lcd.setCursor(10, 0); lcd.print(PCdata[3]); lcd.write(223);

  lcd.setCursor(7, 1);
  sec = (long)(millis() - blink_timer) / 1000;
  hrs = floor((sec / 3600));
  mins = floor(sec - (hrs * 3600)) / 60;
  sec = sec - (hrs * 3600 + mins * 60);
  if (hrs < 10) lcd.print(0);
  lcd.print(hrs);
  lcd.print(":");
  if (mins < 10) lcd.print(0);
  lcd.print(mins);
  lcd.print(":");
  if (sec < 10) lcd.print(0);
  lcd.print(sec);
}

