// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include "OneWire.h"
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 9     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);
OneWire ds(10);

//PWM LED Brightness and Bluetooth Serial Link Demo
//By keuwlsoft:  www.keuwl.com  23rd Aug 2015

int Red_LED_Pin = 6; // PWM Pin for Red LED

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();

  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("Hello, world!");
}

void loop() {

  delay(250);  // Wait a few seconds between measurements.
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Read temperature as Celsius (the default)
//  float f = dht.readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) { // || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
//  float hif = dht.computeHeatIndex(f, h);  // Compute heat index in Fahrenheit (the default)
//  float hic = dht.computeHeatIndex(t, h, false);  // Compute heat index in Celsius (isFahreheit = false)

//  Serial.print("DHT11 Hum.: ");  Serial.print(h);  Serial.print("% ");
//  Serial.print("Temp.: ");  Serial.print(t);  Serial.print("*C ");
//  Serial.print(f);  Serial.print(" *F");
//  Serial.print("Heat index: ");  Serial.print(hic);
//  Serial.print(" *C ");  Serial.print(hif);  Serial.println(" *F");

/*  ----------------------- DS18B20 -----------------------
 *  http://arduino-project.net/podklyuchenie-ds18b20-arduino/ 
 */

  byte data[2];
  ds.reset(); 
  ds.write(0xCC);
  ds.write(0x44);
  delay(750);
  ds.reset();
  ds.write(0xCC);
  ds.write(0xBE);
  data[0] = ds.read(); 
  data[1] = ds.read();
  float Temp = (data[1]<< 8)+data[0];
  Temp = Temp/16;
//  Serial.print(" DS18B20 Temp.: "); Serial.print(Temp); Serial.println("*C ");
  Serial.println("$"); Serial.println(h); Serial.println(" "); Serial.println(t); Serial.println(" "); Serial.println(Temp); Serial.println(";");

  lcd.setCursor(0, 0);  lcd.print(h);  lcd.print("%");
  lcd.setCursor(8, 0);  lcd.print(t);  lcd.print("'C");
  lcd.setCursor(8, 1);  lcd.print(Temp);  lcd.print("'C");

}

void serialEvent(){
  //Process any info coming from the bluetooth serial link
  //Serial.read();
  //Serial.parseInt();
}
