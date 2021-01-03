
void  encoder() {
  
  enc1.tick();
  if (enc1.isLeft() ) itemChng(-1);
  if (enc1.isRight()) itemChng( 1);
  if (enc1.isPress()) mLevelUp();
  
} // ------------------------------------------------------------------

void itemChng (int value) {
    mTimer = millis();  // Menu exit timer reset
    mItem[mLevel] += value;
} // ------------------------------------------------------------------

void mLevelUp () {
    mTimer = millis();  // Menu exit timer reset
    mLevel++;
    if (mLevel == 2) item2 = 0;
    if (mLevel == 3) item3 = chamber[activ].par[item2];
} // ------------------------------------------------------------------
