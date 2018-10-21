// http://robotclass.ru/tutorials/graphics-lcd-nokia-5110/
//-----------------------------------------------------------------------
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 6, 7);
//-----------------------------------------------------------------------
#include "DHT.h"
#define DHTPIN 9     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
//-----------------------------------------------------------------------
void setup(void) {
//  Serial.begin(9600);
  dht.begin();

  display.begin();
  display.setContrast(50); // установка контраста
  delay(1000);
  display.setTextSize(1);  // установка размера шрифта
  display.setTextColor(BLACK); // установка цвета текста
}
//-----------------------------------------------------------------------
void loop(void) {

  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Read temperature as Celsius (the default)
//  Serial.print("Temp.:" + (float)t);
  display.clearDisplay();  display.display();
  display.setCursor(0,0);
  display.print("h.");  display.print(h);
  display.print(" t.");  display.println(t);
  display.display();

  Serial.print("H.");  Serial.print(h);
  Serial.print(" T.");  Serial.println(t);
  delay(250);  // Wait a moment between measurements.

}
//-----------------------------------------------------------------------

