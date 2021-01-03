
void menu() {
  if      (mLevel == 0) menuLevel0();    // Select Temperature / Humidity
  else if (mLevel == 1) menuLevel1();    // Select active Display / Chamber
  else if (mLevel == 2) menuLevel2();    // Select Parameter
  else if (mLevel == 3) menuLevel3();    // Change Selected Value
  else if (mLevel == 4) menuLevel4();    // Store Value
  else mLevel = 0;

  byte idleD = (activ + 1) & 1;          // Idle Display
  disp[idleD].brightness(0);
  disp[idleD].displayByte(sBuf[idleD][sensV]);
} // ------------------------------------------------------------------

void  menuLevel0() {    // Select Temperature / Humidity
  sensV &= 1;
  disp[activ].displayByte(sBuf[activ][sensV]);
} // ------------------------------------------------------------------

void  menuLevel1() {    // Select Active Display / Chamber
  activ &= 1;
  disp[activ].brightness(3);
  menuLevel0();
} // ------------------------------------------------------------------

void  menuLevel2() {    // Select Parameter
  if (item2 < 0) item2 = 9; if (item2 > 9) item2 = 0;
  int value = chamber[activ].par[item2];
  if      (item2 < 4) setPoint(value);
  else if (item2 < 8) mode(value);
  
  disp[activ].point(false);
  disp[activ].displayByte(mBuf[item2]);
} // ------------------------------------------------------------------

void  setPoint (int value) {    // Prepare Setpoint Value
  if (value > 99)   value = 99;
  mBuf[item2][3] = digToHEX(value % 10);
  mBuf[item2][2] = (value > 9) ? digToHEX(value / 10 % 10) : _empty;
} // ------------------------------------------------------------------

void  mode (int value) {        // Prepare Mode Value
  if      (value == 0) { mBuf[item2][2] = _o; mBuf[item2][3] = _F; }
  else if (value == 1) { mBuf[item2][2] = _o; mBuf[item2][3] = _N; }
  else if (value == 2) { mBuf[item2][2] = _A; mBuf[item2][3] = _U; }
} // ------------------------------------------------------------------

void  menuLevel3() {    // Change Selected Value
  if      (item2  < 4) dispInt();
  else if (item2  < 8) ofOnAu();    // Out Mode
  else if (item2 == 8) yesNo();     // Save
  else                 toLevel0();  // Return
} // ------------------------------------------------------------------

void  dispInt() {
  if (item3 < -99) item3 = -99; else if (item3 > 99) item3 = 99;
  disp[activ].displayInt(item3);
} // ------------------------------------------------------------------

void  ofOnAu() {
  if (item3 < 0) item3 = 2; else if (item3 > 2) item3 = 0;
  if      (item3 == 0) disp[activ].displayByte( 0, 0, _o, _F );   // OFF
  else if (item3 == 1) disp[activ].displayByte( 0, 0, _o, _N );   // ON
  else if (item3 == 2) disp[activ].displayByte( 0, 0, _A, _U );   // AUTO
} // ------------------------------------------------------------------

void  yesNo() {
  item3 &= 1;
  if (item3) disp[activ].displayByte( _Y, _E, _S,  0 );  // YES
  else       disp[activ].displayByte( _N, _O,  0,  0 );  // NO
} // ------------------------------------------------------------------

void  toLevel0() {
    disp[activ].point(true);
    disp[activ].brightness(0);
    mLevel = 0;
    activ = 0;
} // ------------------------------------------------------------------

void  menuLevel4() {    // Store Value

  if (item2 == 8) savePar();
  else chamber[activ].par[item2] = item3;
  mLevel = 2;

} // ------------------------------------------------------------------

void  savePar() {
  if (item3 != 1) return;
//  printEEPROM();
  EEPROM.put(activ * 16, chamber[activ].par);
  disp[activ].displayByte( _d, _O, _N, _E );
  delay(2000);
  item3 = 0;
} // ------------------------------------------------------------------

void  printEEPROM() {     // For Testing
  for (int i = 0; i < 8; i++) {
    Serial.print(chamber[0].par[i]);
    Serial.print(" ");
  }
  
  Serial.print("- ");
  
  for (int i = 0; i < 8; i++) {
    Serial.print(chamber[1].par[i]);
    Serial.print(" ");
  }
  Serial.println();

} // ------------------------------------------------------------------

//  Serial.println();
