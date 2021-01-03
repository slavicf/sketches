
void  sensors (byte i) {

//  Serial.print((int) mLevel);  Serial.print(" ");  Serial.print((int) sensV);  Serial.print(" ");  Serial.print((int) activ);  Serial.print(" ");  Serial.print((int) item2);  Serial.print(" ");  Serial.print((int) item3);  Serial.println();

  chamber[i].temp = iSensor(sBuf[i][0], dht[i].readTemperature() + (float) chamber[i].par[2] *0.1);
  chamber[i].hum  = iSensor(sBuf[i][1], dht[i].readHumidity() + (float) chamber[i].par[3] * 0.1);
} // ------------------------------------------------------------------

int iSensor(uint8_t buf[], float value) {
  if (isnan(value)) {
    buf[0] = _E; buf[1] = _r; buf[2] = _r;
    return 999;
  } else {
    int val = value * 10;
    dhtToArray(buf, 2, val);
    return (val > 999) ? 999 : val;
  }
} // ------------------------------------------------------------------

void  dhtToArray(uint8_t arr[], int pos, int value) {
  arr[pos] = digToHEX(value % 10);
  if (pos > 0) dhtToArray(arr, --pos, value / 10);
} // ------------------------------------------------------------------

//  Serial.print((int) mLevel);  Serial.print(" ");  Serial.print((int) sensV);  Serial.print(" ");  Serial.print((int) activ);  Serial.print(" ");  Serial.print((int) item2);  Serial.print(" ");  Serial.print((int) item3);  Serial.println();
