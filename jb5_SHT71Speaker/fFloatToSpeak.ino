/*
  21 - Degree 1
  22 - Degree 2-4
  25 - Degree 5-0
  27 - Temperature
  31 - Percent 1
  32 - Percent 2-4
  35 - Percent 5-0
  37 - Humidity
  41 - Error
  42 - Minus
  43 - Plus
  44 - And

 */
int floatToSpeak(float f) {
  
  int value = round(f * 10.0);  //Serial.print(" Value1: ");  Serial.print(value);
//  value = value % 10000;  Serial.print(" Value2: ");  Serial.print(value);
  
  if (value < 0) {
    value = abs(value);  //Serial.print(" Absolute Value: ");  Serial.print(value);
    bufPush(42);  // Minus
  }

  int iTemp = 25; // Degree 5-0
  
  int hundred = value / 1000;
  value = value % 1000;
  
  int ten = value / 100;
  value = value % 100;
  
  int one = value / 10;
  value = value % 10;
  
  int tenths = value;
  
  if (hundred > 0) {
    bufPush(100);
  }
  
  if (ten > 1) {
    bufPush(ten * 10);
  }
  
  if (ten == 1) {
    bufPush(10 + one);
  } else if (one > 0) {
    bufPush(one);
    iTemp = degrPerc(one);
  }

  if (tenths > 0) {
    if (f < 1.0) {
      bufPush(one);
    }
    bufPush(44);  // And
    bufPush(tenths);
    iTemp = degrPerc(tenths);
  }

  if (f == 0.0) {
    bufPush(0);
  }

  return iTemp;

}

int degrPerc (int value) {
  int iTemp = 25; // Degree 5-0
  if (value == 1) iTemp = 21;  // Degree 1
  if (value > 1  && value < 5) iTemp = 22;  // Degree 2-4
  return iTemp;
}
