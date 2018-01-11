//-----------------------------------------------------------------------
void UpdateData() {
  if (bReadTime) UpdateTime();
  if (bReadDHT22) UpdateDHT22();
  if (Serial.available() > 0) parsing();
}
//-----------------------------------------------------------------------
void UpdateTime() {
  //  t = now();
  breakTime(now(), tm);
  bReadTime = 0;
}
//-----------------------------------------------------------------------
void UpdateDHT22() {
  fTemperature = dht.readTemperature();  // Read temperature as Celsius (the default)
  fHumidity = dht.readHumidity();
  bReadDHT22 = 0;
}
//-----------------------------------------------------------------------
void parsing() {
  //  while (Serial.available() > 0) {
  char aChar = Serial.read();
  if (aChar != 'E') {
    inData[index] = aChar;
    index++;
    inData[index] = '\0';
  } else {
    char *p = inData;
    char *str;
    index = 0;
    String value = "";
    while ((str = strtok_r(p, ";", &p)) != NULL) {
      string_convert = str;
      PCdata[index] = string_convert.toInt();
      index++;
    }
    index = 0;
    bUpdateDisplay = 1;
  }
  ulTimeout = millis();
  bTimeOut = 1;
  //  }
}

