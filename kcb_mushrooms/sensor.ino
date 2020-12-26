
void  sensors (byte i) {
  
  chamber[i].temp = dht[i].readTemperature() * 10;
  chamber[i].hum = dht[i].readHumidity() * 10;
  if (chamber[i].hum > 999) chamber[i].hum = 999;
  dhtToArray(&L0Buffer[0 + i * 2][0], 2, chamber[i].temp);
  dhtToArray(&L0Buffer[1 + i * 2][0], 2, chamber[i].hum);
  
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
