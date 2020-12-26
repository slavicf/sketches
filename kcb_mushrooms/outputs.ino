
void outputs() {
//  serOut(output);
//  output++;
//  Serial.println(output);

  hyst(0);
  hyst(1);

//  if (chamber[0].par[1] * 10 >= chamber[0].hum  + hysteresis)  chamber[0].a[0] = 1;   // Auto Out fan
//  if (chamber[0].par[1] * 10 <  chamber[0].hum              )  chamber[0].a[0] = 0;
//  if (chamber[0].par[0] * 10 >= chamber[0].temp + hysteresis)  chamber[0].a[1] = 1;   // Auto In fan
//  if (chamber[0].par[0] * 10 <  chamber[0].temp)               chamber[0].a[1] = 0;

  bool  b[8];
  if (chamber[0].par[2] == 2) b[0] = chamber[0].a[0];  else b[0] = chamber[0].par[2];
  if (chamber[0].par[3] == 2) b[1] = chamber[0].a[1];  else b[1] = chamber[0].par[3];
  if (chamber[0].par[4] == 2) b[2] = chamber[0].a[2];  else b[2] = chamber[0].par[4];
  if (chamber[0].par[5] == 2) b[3] = chamber[0].a[3];  else b[3] = chamber[0].par[5];
  if (chamber[1].par[2] == 2) b[4] = chamber[1].a[0];  else b[4] = chamber[1].par[2];
  if (chamber[1].par[3] == 2) b[5] = chamber[1].a[1];  else b[5] = chamber[1].par[3];
  if (chamber[1].par[4] == 2) b[6] = chamber[1].a[2];  else b[6] = chamber[1].par[4];
  if (chamber[1].par[5] == 2) b[7] = chamber[1].a[3];  else b[7] = chamber[1].par[5];
  
  output = (b[0] << 0) + (b[1] << 1) + (b[2] << 2) + (b[3] << 3) + (b[4] << 4) + (b[5] << 5) + (b[6] << 6) + (b[7] << 7);
  expander.write8(~output);
//  output++;
} // ------------------------------------------------------------------

void  hyst (byte chamb) {
  if (chamber[chamb].temp <  chamber[chamb].par[0] * 10 - hysteresis)  chamber[chamb].a[3] = 1;   // Auto Heater
  if (chamber[chamb].temp >= chamber[chamb].par[0] * 10)               chamber[chamb].a[3] = 0;
  if (chamber[chamb].hum  <  chamber[chamb].par[1] * 10 - hysteresis)  chamber[chamb].a[2] = 1;   // Auto Humidifier
  if (chamber[chamb].hum  >= chamber[chamb].par[1] * 10)               chamber[chamb].a[2] = 0;
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
