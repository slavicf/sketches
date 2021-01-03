
void  encoder() {
  
  enc1.tick();
  if (enc1.isLeft() ) itemChng(-1);
  if (enc1.isRight()) itemChng( 1);
  if (enc1.isPress()) {
    m.timer = millis();  // Menu exit timer reset
    m.level++;
    if (m.level == 3) item3 = chamber[activ].par[item2]; // / 10;
  }
  
} // ------------------------------------------------------------------

void itemChng (int value) {
    m.timer = millis();  // Menu exit timer reset
    m.item[m.level] += value;
} // ------------------------------------------------------------------
