
#include "DHT.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 9     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
#define RelayControl 10   //RS485 управляющий контакт на arduino pin 10
#define DTMF_StQ 8   //RS485 управляющий контакт на arduino pin 10

bool StQ = false;
int Relay = 0;
//-----------------------------------------------------------------------
void setup(void) {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  
  pinMode(RelayControl, OUTPUT);  
  pinMode(DTMF_StQ, INPUT);  
}
//-----------------------------------------------------------------------
void loop(void) {
   
  StQ = !digitalRead(8);
  digitalWrite(10, StQ);
  
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

