//-----------------------------------------------------------------------
void readData() {
  if (bReadTime) readTime();
  if (bReadDHT22) readDHT22();
  parsing();
}
//-----------------------------------------------------------------------
void readTime() {
//  t = now();
  breakTime(now(), tm);
  bReadTime = 0;
}
//-----------------------------------------------------------------------
void readDHT22() {
  fTemperature = dht.readTemperature();  // Read temperature as Celsius (the default)
  fHumidity = dht.readHumidity();
  bReadDHT22 = 0;
}
//-----------------------------------------------------------------------
void parsing() {
  while (Serial.available() > 0) {
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
//      if (PCdata[4] > 99) PCdata[4] = 99;
//      if (PCdata[5] > 99) PCdata[5] = 99;
//      sCPUtemp = num2str(PCdata[0], 7);
//      sCPUload = num2str(PCdata[4], '%');
//      sGPUtemp = num2str(PCdata[1], 7);
//      sGPUload = num2str(PCdata[5], '%');
      index = 0;
      bUpdateDisplay = 1;
    }
    ulTimeout = millis();
    bTimeOut = 1;
  }
}
