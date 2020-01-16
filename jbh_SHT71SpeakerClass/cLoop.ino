
void loop() {

  static bool playReq = false; // play request
  static bool firstCycle = true;
  float temperature;    // SHT7x Temperature variable
  float humidity;       // SHT7x Humidity variable
  float dewpoint;       // SHT7x DewPoint variable
//  static unsigned long timer = millis();

  bool playing = !digitalRead(DFP_BUSY);   // playing now
  if(playing)  playReq = false;
  digitalWrite(LED_BUILTIN, sensor.update());
//  if ((Serial.available() > 0) || firstCycle || (sensor && !sensorOld)) {
  if (sensor.pos() && firstCycle) {
    firstCycle = false;

    tempSensor.measure(&temperature, &humidity, &dewpoint);
    Serial.print("Temperature: ");  Serial.print(temperature);  Serial.print(" C, Humidity: ");
    Serial.print(humidity);  Serial.print(" %, Dewpoint: ");  Serial.print(dewpoint);  Serial.println(" C");

    floatToSpeak(27, temperature);
    floatToSpeak(37, humidity);
//    floatToSpeak(dewpoint);
  }

  if (!playReq && !playing) {
    if(!buf.empty()) {
      byte volume = (analogRead(0) >> 6) << 1;
      myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
      myDFPlayer.playFolder(1, buf.pull());
      playReq = true;
    }
  }

//  if (millis() - timer > 1000) {
//    timer = millis();
//    Serial.print(" Analog input: ");  Serial.print(volume);
//    Serial.print(" DFP_State:");  Serial.print(DFP_State);
//    Serial.print(" DFP_Busy:");  Serial.print(DFP_Busy);
//    Serial.println();
//  }

}
