
void outputs() {
//  serOut(output);

  hyst(0);
  hyst(1);

//  if (chamber[0].par[1] * 10 >= chamber[0].hum  + hysteresis)  chamber[0].a[0] = 1;   // Auto Out fan
//  if (chamber[0].par[1] * 10 <  chamber[0].hum              )  chamber[0].a[0] = 0;
//  if (chamber[0].par[0] * 10 >= chamber[0].temp + hysteresis)  chamber[0].a[1] = 1;   // Auto In fan
//  if (chamber[0].par[0] * 10 <  chamber[0].temp)               chamber[0].a[1] = 0;

//  bool  b[8];
//  if (chamber[0].par[2] == 2) b[0] = chamber[0].a[0];  else b[0] = chamber[0].par[2];
//  if (chamber[0].par[3] == 2) b[1] = chamber[0].a[1];  else b[1] = chamber[0].par[3];
//  if (chamber[0].par[4] == 2) b[2] = chamber[0].a[2];  else b[2] = chamber[0].par[4];
//  if (chamber[0].par[5] == 2) b[3] = chamber[0].a[3];  else b[3] = chamber[0].par[5];
//  if (chamber[1].par[2] == 2) b[4] = chamber[1].a[0];  else b[4] = chamber[1].par[2];
//  if (chamber[1].par[3] == 2) b[5] = chamber[1].a[1];  else b[5] = chamber[1].par[3];
//  if (chamber[1].par[4] == 2) b[6] = chamber[1].a[2];  else b[6] = chamber[1].par[4];
//  if (chamber[1].par[5] == 2) b[7] = chamber[1].a[3];  else b[7] = chamber[1].par[5];
//  
//  output = (b[0] << 0) + (b[1] << 1) + (b[2] << 2) + (b[3] << 3) + (b[4] << 4) + (b[5] << 5) + (b[6] << 6) + (b[7] << 7);
  
  output = (manAuto( 0, 2 ) << 0) + (manAuto( 0, 3 ) << 1) + (manAuto( 0, 4 ) << 2) + (manAuto( 0, 5 ) << 3) + 
           (manAuto( 1, 2 ) << 4) + (manAuto( 1, 3 ) << 5) + (manAuto( 1, 4 ) << 6) + (manAuto( 1, 5 ) << 7);
  expander.write8(output);

//  output++;
//  Serial.println(output);
} // ------------------------------------------------------------------

bool manAuto (byte i, byte k) {

  return (chamber[i].par[k] == 2) ? chamber[i].a[k-2] : chamber[i].par[k];
  
} // ------------------------------------------------------------------

void  hyst (byte i) {
  if (chamber[i].temp <  chamber[i].par[0] * 10 - hysteresis)  chamber[i].a[3] = 1;   // Auto Heater
  if (chamber[i].temp >= chamber[i].par[0] * 10)               chamber[i].a[3] = 0;
  if (chamber[i].hum  <  chamber[i].par[1] * 10 - hysteresis)  chamber[i].a[2] = 1;   // Auto Humidifier
  if (chamber[i].hum  >= chamber[i].par[1] * 10)               chamber[i].a[2] = 0;
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
