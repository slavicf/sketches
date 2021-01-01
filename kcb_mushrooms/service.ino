void  service() {

  encoder();

  if (millis() - pTimer > pCycle) {
    pTimer = millis();

    if ((phase & 0x0F) == 0) sensors(0); // 3.2 sec
    if ((phase & 0x0F) == 8) sensors(1); // 3.2 sec
    menu();    //    if ((phase & 0x01) == 1) displ(); // 0.2 sec
    if ((phase & 0x03) == 3) outputs(); // 0.8 sec

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
