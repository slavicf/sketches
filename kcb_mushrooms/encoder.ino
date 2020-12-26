
void  encoder() {
  
  enc1.tick();
  if (enc1.isLeft()) {
    menuItem[menuLevel]--;
    mTimer = millis();  // Menu exit timer reset
  }
  if (enc1.isRight()) {
    menuItem[menuLevel]++;
    mTimer = millis();  // Menu exit timer reset
  }
  if (enc1.isPress()) {
    menuLevel++;
    mTimer = millis();  // Menu exit timer reset
    if (menuLevel == 3) {
      menuItem[3] = chamber[menuItem[1]].par[menuItem[2]]; // / 10;
    }
  }
  
} // ------------------------------------------------------------------
