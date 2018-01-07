
void draw_labels_11() {
  lcd.createChar(0, degree);
  lcd.createChar(1, left_empty);
  lcd.createChar(2, center_empty);
  lcd.createChar(3, right_empty);
  lcd.createChar(4, row8);
  lcd.setCursor(0, 0);
  lcd.print("CPU:");
  lcd.setCursor(0, 1);
  lcd.print("GPU:");
}
void draw_labels_12() {
  lcd.createChar(0, degree);
  lcd.createChar(1, left_empty);
  lcd.createChar(2, center_empty);
  lcd.createChar(3, right_empty);
  lcd.createChar(4, row8);
  lcd.setCursor(0, 0);
  lcd.print("GPUmem:");
  lcd.setCursor(0, 1);
  lcd.print("RAMuse:");
}
void draw_labels_21() {
  lcd.createChar(0, degree);
  lcd.createChar(1, left_empty);
  lcd.createChar(2, center_empty);
  lcd.createChar(3, right_empty);
  lcd.createChar(4, row8);

  lcd.setCursor(0, 0);
  lcd.print("FANsp:");
  lcd.setCursor(0, 1);
  lcd.print("T1: ");
  lcd.setCursor(8, 1);
  lcd.print("T2:");
}
void draw_labels_22() {
  lcd.createChar(0, degree);
  lcd.createChar(1, left_empty);
  lcd.createChar(2, center_empty);
  lcd.createChar(3, right_empty);
  lcd.createChar(4, row8);

  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.setCursor(7, 0);
  lcd.print("HM:");
  lcd.setCursor(0, 1);
  lcd.print("UPTIME:");
}

void draw_legend() {
  byte data = PCdata[plotLines[display_mode]];
  lcd.setCursor(10, 0); lcd.print(data);
  if (display_mode > 1) {
    if (data < 10) perc = "% ";
    else if (data < 100) perc = "%";
    else {
      perc = "";
    }
    lcd.print(perc);
  } else {
    if (data < 10) {
      lcd.write(223);
      lcd.print("  ");
    } else if (data < 100) {
      lcd.write(223); lcd.print(" ");
    } else {
      lcd.write(223);
    }
  }
}

void draw_plot() {
  draw_legend();

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.printByte(constrain(map(PLOTmem[display_mode][i], 0, 100, 0, 7), 0, 7));
  }
}

void draw_plot_symb() {
  lcd.createChar(0, row1);
  lcd.createChar(1, row2);
  lcd.createChar(2, row3);
  lcd.createChar(3, row4);
  lcd.createChar(4, row5);
  lcd.createChar(5, row6);
  lcd.createChar(6, row7);
  lcd.createChar(7, row8);
  lcd.setCursor(0, 0);
  lcd.print(plotNames0[display_mode]);
  lcd.setCursor(3, 0);
  lcd.print(plotNames1[display_mode]);
  lcd.print(": ");
}

