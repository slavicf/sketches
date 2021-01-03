
void menu() {

//  m.level = constrain(menuLevel, 0, 4);
  if      (m.level == 0) menuLevel0();    // Select Temperature / Humidity
  else if (m.level == 1) menuLevel1();    // Select active Display / Chamber
  else if (m.level == 2) menuLevel2();    // Select Parameter
  else if (m.level == 3) menuLevel3();    // Change Selected Value
  else if (m.level == 4) menuLevel4();    // Store Value
  else m.level = 0;

  byte idleD = (activ + 1) & 1;           // Idle Display
  disp[idleD].brightness(0);
  disp[idleD].displayByte(L0Buffer[sensV + idleD * 2]);
  
} // ------------------------------------------------------------------

void  menuLevel0() {    // Select Temperature / Humidity

  sensV &= 1;
  disp[activ].displayByte(L0Buffer[sensV + activ * 2]);

} // ------------------------------------------------------------------

void  menuLevel1() {    // Select Active Display / Chamber

  activ &= 1;
  disp[activ].brightness(3);
  menuLevel0();
  item2 = 0;

} // ------------------------------------------------------------------

void  menuLevel2() {    // Select Parameter

  item2 &= 7;
  int value = chamber[activ].par[item2];
  if      (item2 < 2) setPoint(value);
  else if (item2 < 6) mode(value);
  
  disp[activ].point(false);
  disp[activ].displayByte(L2Buffer[item2]);

} // ------------------------------------------------------------------

void  setPoint (int value) {    // Prepare Setpoint Value
  if (value > 99)   value = 99;
  L2Buffer[item2][3] = digToHEX(value % 10);
  if (value > 9) L2Buffer[item2][2] = digToHEX(value / 10 % 10);
  else L2Buffer[item2][2] = _empty;
} // ------------------------------------------------------------------

void  mode (int value) {        // Prepare Mode Value
  if      (value == 0) { L2Buffer[item2][2] = _o; L2Buffer[item2][3] = _F; }
  else if (value == 1) { L2Buffer[item2][2] = _o; L2Buffer[item2][3] = _N; }
  else if (value == 2) { L2Buffer[item2][2] = _A; L2Buffer[item2][3] = _U; }
  
} // ------------------------------------------------------------------

void  menuLevel3() {    // Change Selected Value

  if      (item2 < 2)  disp[activ].displayInt(item3);
  else if (item2 < 6) {
    if      (item3 <  0) item3 = 2;
    else if (item3 >  2) item3 = 0;
    if      (item3 == 0) disp[activ].displayByte( 0, 0, _o, _F );   // OFF
    else if (item3 == 1) disp[activ].displayByte( 0, 0, _o, _N );   // ON
    else if (item3 == 2) disp[activ].displayByte( 0, 0, _A, _U );   // AUTO
    
  } else if (item2 == 6) {  // Save
    item3 &= 1;
    if (item3) disp[activ].displayByte( _Y, _E, _S,  0 );  // YES
    else       disp[activ].displayByte( _N, _O,  0,  0 );  // NO
    //    m.level = 2;
    
  }  else {  // Return
    toLevel0();
  }

} // ------------------------------------------------------------------
void  toLevel0() {
    disp[activ].point(true);
    disp[activ].brightness(0);
    m.level = 0;
    activ = 0;
} // ------------------------------------------------------------------

void  menuLevel4() {    // Store Value

  if (item2 == 6) {  // Save
    if (item3) {
      EEPROM.put(activ * 12, chamber[activ].par);
//      printEEPROM();
      item3 = 0;
      disp[activ].displayByte( _D, _O, _N, _E );
      delay(2000);
    }
  }
  chamber[activ].par[item2] = item3;
  m.level = 2;

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
