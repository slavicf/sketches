
void menu() {
  if (menuLevel == 0) menuLevel0(0, 0);
  if (menuLevel == 1) menuLevel1();
  if (menuLevel == 2) menuLevel2();
  if (menuLevel == 3) menuLevel3();
  if (menuLevel == 4) menuLevel4();

} // ------------------------------------------------------------------

void  menuLevel0(uint8_t screen0, uint8_t screen1) {

  menuItem[0] &= 0x01;
  setBright(screen0, screen1);
  disp[0].point(true);
  disp[1].point(true);

  disp[0].displayByte(L0Buffer[menuItem[0]]);
  disp[1].displayByte(L0Buffer[menuItem[0] + 2]);

} // ------------------------------------------------------------------

void  menuLevel1() {

  menuItem[1] &= 1;
  if (menuItem[1] == 0) {
    menuLevel0(3, 0);
  } else if (menuItem[1] == 1) {
    menuLevel0(0, 3);
  }

} // ------------------------------------------------------------------

void  menuLevel2() {

  if (menuItem[2] < 0) menuItem[2] = 7;
  if (menuItem[2] > 7) menuItem[2] = 0;

  disp[menuItem[1]].point(false);
  disp[menuItem[1]].displayByte(L2Buffer[menuItem[2]]);
  byte idleDisplay = (menuItem[1] + 1) & 1;
  disp[idleDisplay].displayByte(L0Buffer[menuItem[0] + idleDisplay * 2]);

} // ------------------------------------------------------------------

void  menuLevel3() {

  if (menuItem[2] == 7) {  // Return
    menuLevel = 0;
    menuItem[2] = 0;
  } else if (menuItem[2] == 6) {  // Save
    menuItem[3] &= 1;
    if (menuItem[3]) disp[menuItem[1]].displayByte( _Y, _E, _S, _empty );
    else             disp[menuItem[1]].displayByte( _N, _O, _empty, _empty );
    //    menuLevel = 2;
  } else if (menuItem[2] == 0 || menuItem[2] == 1) {
    disp[menuItem[1]].displayInt(menuItem[3]);
  } else {
    if (menuItem[3] < 0) menuItem[3] = 2;
    if (menuItem[3] > 2) menuItem[3] = 0;
    if (menuItem[3] == 0) disp[menuItem[1]].displayByte( _O, _F, _F, _empty );
    if (menuItem[3] == 1) disp[menuItem[1]].displayByte( _O, _n, _empty, _empty );
    if (menuItem[3] == 2) disp[menuItem[1]].displayByte( _A, _u, _t, _o );
  }
  byte idleDisplay = (menuItem[1] + 1) & 1;
  disp[idleDisplay].displayByte(L0Buffer[menuItem[0] + idleDisplay * 2]);

} // ------------------------------------------------------------------

void  menuLevel4() {

  if (menuItem[2] == 6) {  // Save
    if (menuItem[3]) {
      EEPROM.put(menuItem[1] * 12, chamber[menuItem[1]].par);
      printEEPROM();
      menuItem[3] = 0;
      disp[menuItem[1]].displayByte( _D, _O, _N, _E );
      delay(2000);
    }
  }
  chamber[menuItem[1]].par[menuItem[2]] = menuItem[3]; // * 10;
  menuLevel = 2;

} // ------------------------------------------------------------------

void  printEEPROM() {
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

void setBright(uint8_t screen0, uint8_t screen1) {
  disp[0].brightness(screen0);
  disp[1].brightness(screen1);

} // ------------------------------------------------------------------

//  Serial.println();
