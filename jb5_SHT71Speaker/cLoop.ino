
void loop() {
//  static unsigned long timer = millis();
//  old_State = DFP_State;
//  DFP_State = myDFPlayer.readState();
  playing = !digitalRead(busyPin);
  sensorOld = sensor;
  sensor = digitalRead(sensorPin);
  if(playing)  playReq = false;
  digitalWrite(LED_BUILTIN, sensor);
//  digitalWrite(LED_BUILTIN, playReq);

//  if ((Serial.available() > 0) || firstCycle || (sensor && !sensorOld)) {
  if (sensor && !sensorOld) {
    int iTemp;
    
    tempSensor.measure(&temperature, &humidity, &dewpoint);
    Serial.print("Temperature: ");  Serial.print(temperature);  Serial.print(" C, Humidity: ");
    Serial.print(humidity);  Serial.print(" %, Dewpoint: ");  Serial.print(dewpoint);  Serial.println(" C");

//    float a = Serial.parseFloat();
//    Serial.read();
    
    bufPush(27);  // Temperature
    iTemp = floatToSpeak(temperature);
    bufPush(iTemp);  // Degree
    
    bufPush(37);  //Humidity
    iTemp = floatToSpeak(humidity);
    bufPush(iTemp + 10);  // Percent
    
//    floatToSpeak(dewpoint);
  }

  if (!playReq && !playing) {
    if(bufHead != bufTail) {
      myDFPlayer.playFolder(1, bufPull());
      playReq = true;
    }
  }

//  if (millis() - timer > 250) {
//    timer = millis();
//    Serial.print(" DFP_State:");  Serial.print(DFP_State);
//    Serial.print(" DFP_Busy:");  Serial.print(DFP_Busy);
//    Serial.println();
//  }

  firstCycle = false;
}
