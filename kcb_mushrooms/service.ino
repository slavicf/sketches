void  service() {

  encoder();

  if (millis() - pTimer > pCycle) {
    pTimer = millis();

    if ((phase & 0x0F) == 0) sensors(0);  // 1.6 sec
    if ((phase & 0x0F) == 8) sensors(1);  // 1.6 sec
    menu();                               // 0.1 sec
    if ((phase & 0x03) == 3) outputs();   // 0.4 sec

    phase++;
  }

  if (menuLevel > 0) {  // Menu exit timer
    if (millis() - mTimer > mCycle) {
      mTimer = millis();  // Menu exit timer reset
      if (menuLevel == 2 || menuLevel == 1) menuItem[menuLevel] = 0;
      menuLevel--;
    }
  }

} // ------------------------------------------------------------------

//    Serial.print("Phase ");
//    Serial.print(phase);
//    Serial.print(", phase & 0x0F = ");
//    Serial.print(phase & 0x0F);
//    Serial.println();
