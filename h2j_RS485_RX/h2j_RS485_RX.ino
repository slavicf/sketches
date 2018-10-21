
#include "DHT.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 9     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
#define SerialTxControl 10   //RS485 управляющий контакт на arduino pin 10
#define RS485Transmit    HIGH
#define RS485Receive     LOW  

char buffer[100];

int i;

//-----------------------------------------------------------------------
void setup(void) {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  
  pinMode(SerialTxControl, OUTPUT);  
  digitalWrite(SerialTxControl, RS485Receive);
  //digitalWrite(SerialTxControl, RS485Transmit);
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

  delay(100);
  i=0;
  
  lcd.setCursor(0, 1);
  while( Serial.available() && i< 99) {
    buffer[i] = Serial.read();
    int a = int(buffer[i++]);
    lcd.print(a, HEX);
  }
  lcd.print("    ");
  //buffer[i++]='\0';

  //Serial.println(buffer); // Выводим что приняли с других устройств

}
//-----------------------------------------------------------------------

