
void outputs() {

  autoMode();
  byte output = (manAuto( 0, 4 ) << 0) + (manAuto( 0, 5 ) << 1) + (manAuto( 0, 6 ) << 2) + (manAuto( 0, 7 ) << 3) + 
                (manAuto( 1, 4 ) << 4) + (manAuto( 1, 5 ) << 5) + (manAuto( 1, 6 ) << 6) + (manAuto( 1, 7 ) << 7);
  expander.write8(output);

//  serOut(output);
//  output++;
//  Serial.println(output);
} // ------------------------------------------------------------------

void  autoMode () {
  hyst(chamber[0].temp, chamber[0].par[0] * 10, chamber[0].a[3]);
  hyst(chamber[0].hum , chamber[0].par[1] * 10, chamber[0].a[2]);
  hyst(chamber[1].temp, chamber[1].par[0] * 10, chamber[1].a[3]);
  hyst(chamber[1].hum , chamber[1].par[1] * 10, chamber[1].a[2]);
} // ------------------------------------------------------------------

void  hyst (int pv, int sp, int &autoOut) {
  if (pv <  sp - hysteresis)  autoOut = 1;
  if (pv >= sp)               autoOut = 0;
} // ------------------------------------------------------------------

bool manAuto (byte i, byte k) {
  return (chamber[i].par[k] == 2) ? chamber[i].a[k-4] : chamber[i].par[k];
} // ------------------------------------------------------------------

//void  serOut(uint8_t out) {
//  for (int i = 0; i < 8; i++) {
//    digitalWrite(SER, out & 1);
//    out >>= 1;
//    digitalWrite(SRCLK, HIGH);
//    digitalWrite(SRCLK, LOW);
//  }
//  digitalWrite(RCLK, HIGH);
//  digitalWrite(RCLK, LOW);
//} // ------------------------------------------------------------------

//  Serial.println();
