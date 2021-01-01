
void  sensors (byte i) {
  float t = dht[i].readTemperature();
  float h = dht[i].readHumidity();
  byte pTemp = i * 2;
  byte pHum  = pTemp + 1;
  if (isnan(t) || isnan(h)) {
    chamber[i].temp = 999;
    chamber[i].hum  = 999;
    L0Buffer[pTemp][0] = _n;  L0Buffer[pTemp][1] = _A;  L0Buffer[pTemp][2] = _n;
    L0Buffer[pHum ][0] = _n;  L0Buffer[pHum ][1] = _A;  L0Buffer[pHum ][2] = _n;
  } else {
    chamber[i].temp = t * 10;
    chamber[i].hum  =  h * 10;
    if (chamber[i].hum > 999) chamber[i].hum = 999;
    dhtToArray(&L0Buffer[pTemp][0], 2, chamber[i].temp);
    dhtToArray(&L0Buffer[pHum ][0], 2, chamber[i].hum);
  }
  
} // ------------------------------------------------------------------

void  dhtToArray(uint8_t *pointer, int pos, int value) {
  
  pointer[pos] = digToHEX(value % 10);
  if (pos > 0) dhtToArray(&pointer[0], --pos, value / 10);
  
} // ------------------------------------------------------------------

//void dht( int n, float h, float t) {
//  if (isnan(h) || isnan(t)) {
//    Serial.print(F("Failed to read from DHT sensor!"));
//    return;
//  }
//  Serial.print(F("H"));
//  Serial.print(n);
//  Serial.print(F(": "));
//  Serial.print(h);
//  Serial.print(F("% T"));
//  Serial.print(n);
//  Serial.print(F(": "));
//  Serial.print(t);
//  Serial.print(F("    "));
//} // ------------------------------------------------------------------
