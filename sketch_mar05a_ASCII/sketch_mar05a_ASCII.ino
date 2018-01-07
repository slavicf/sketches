//  Программа для дистанционного управления блоком ПВ-310
#include "DHT.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 9     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

char buffer[100];
int i;

//-----------------------------------------------------------------------
void setup(void) {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  
}
//-----------------------------------------------------------------------
void loop(void) {
   
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Read temperature as Celsius (the default)
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(h, 1);  lcd.print("%  ");  lcd.print(t, 1);  lcd.print("'C");
  //lcd.print(h, 1);  lcd.print("%  ");  lcd.print(t, 1);  lcd.print("'C");
  //lcd.scrollDisplayLeft();
  delay(250);  // Wait a few seconds between measurements.

}
//-----------------------------------------------------------------------
void serialEvent(){

  delay(50);
  i=0;
  
  lcd.setCursor(0, 1);
  while( Serial.available() && i< 99) {
    byte a = Serial.read();
    if (a == '\r') a = 'r';
    if (a == '\n') a = 'n';
    buffer[i++] = a;
  }
  buffer[i]='\0';
  lcd.print(buffer);

}

