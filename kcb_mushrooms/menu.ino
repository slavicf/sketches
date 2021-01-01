
void menu() {
  if (menuLevel == 0) menuLevel0(0, 0);   // Select Temperature / Humidity
  if (menuLevel == 1) menuLevel1();       // Select active Display / Chamber
  if (menuLevel == 2) menuLevel2();       // Select Parameter
  if (menuLevel == 3) menuLevel3();       // Change Selected Value
  if (menuLevel == 4) menuLevel4();       // Store Value

} // ------------------------------------------------------------------

void  menuLevel0(uint8_t screen0, uint8_t screen1) {    // Select Temperature / Humidity

  menuItem[0] &= 1;
  setBright(screen0, screen1);
  disp[0].point(true);
  disp[1].point(true);

  disp[0].displayByte(L0Buffer[menuItem[0]]);
  disp[1].displayByte(L0Buffer[menuItem[0] + 2]);

} // ------------------------------------------------------------------

void setBright(uint8_t i, uint8_t k) {      // Set Displays Brightness
  disp[0].brightness(i);
  disp[1].brightness(k);

} // ------------------------------------------------------------------

void  menuLevel1() {    // Select Active Display / Chamber

  menuItem[1] &= 1;
  if (menuItem[1] == 0) {
    menuLevel0(3, 0);
  } else if (menuItem[1] == 1) {
    menuLevel0(0, 3);
  }

} // ------------------------------------------------------------------

void  menuLevel2() {    // Select Parameter

  menuItem[2] &= 7;
  if (menuItem[2] < 6) l2Display();
  
  disp[menuItem[1]].point(false);
  disp[menuItem[1]].displayByte(L2Buffer[menuItem[2]]);
  byte idleDisplay = (menuItem[1] + 1) & 1;
  disp[idleDisplay].displayByte(L0Buffer[menuItem[0] + idleDisplay * 2]);

} // ------------------------------------------------------------------

void  l2Display () {    // Display Parameter Value
  int value = chamber[menuItem[1]].par[menuItem[2]];
  L2Buffer[menuItem[2]][3] = digToHEX(value % 10);
  if (value > 9) L2Buffer[menuItem[2]][2] = digToHEX(value / 10 % 10);
  else L2Buffer[menuItem[2]][2] = _empty;
} // ------------------------------------------------------------------

void  menuLevel3() {    // Change Selected Value

  if (menuItem[2] < 2) {
    disp[menuItem[1]].displayInt(menuItem[3]);
    
  }  else if (menuItem[2] < 6) {
    if (menuItem[3] < 0) menuItem[3] = 2;
    if (menuItem[3] > 2) menuItem[3] = 0;
    if (menuItem[3] == 0) disp[menuItem[1]].displayByte( _O, _F, _F, 0 );   // OFF
    if (menuItem[3] == 1) disp[menuItem[1]].displayByte( _O, _n, 0, 0 );   // ON
    if (menuItem[3] == 2) disp[menuItem[1]].displayByte( _A, _u, _t, _o );   // AUTO
    
  }  else if (menuItem[2] == 6) {  // Save
    menuItem[3] &= 1;
    if (menuItem[3]) disp[menuItem[1]].displayByte( _Y, _E, _S, 0 );  // YES
    else             disp[menuItem[1]].displayByte( _N, _O, 0, 0 );  // NO
    //    menuLevel = 2;
    
  }  else {  // Return
    menuLevel = 0;
    menuItem[1] = 0;
    menuItem[2] = 0;
  }
  
  byte idleDisplay = (menuItem[1] + 1) & 1;
  disp[idleDisplay].displayByte(L0Buffer[menuItem[0] + idleDisplay * 2]);

} // ------------------------------------------------------------------

void  menuLevel4() {    // Store Value

  if (menuItem[2] == 6) {  // Save
    if (menuItem[3]) {
      EEPROM.put(menuItem[1] * 12, chamber[menuItem[1]].par);
//      printEEPROM();
      menuItem[3] = 0;
      disp[menuItem[1]].displayByte( _D, _O, _N, _E );
      delay(2000);
    }
  }
  chamber[menuItem[1]].par[menuItem[2]] = menuItem[3];
  menuLevel = 2;

} // ------------------------------------------------------------------

void  printEEPROM() {     // For Testing
  for (int i = 0; i < 6; i++) {
    Serial.print(chamber[0].par[i]);
    Serial.print(" ");
  }

  Serial.println();

  for (int i = 0; i < 6; i++) {
    Serial.print(chamber[1].par[i]);
    Serial.print(" ");
  }

  Serial.println();

} // ------------------------------------------------------------------

//  Serial.println();
