/*
 *  https://uscr.ru/kak-podklyuchit-chasy-realnogo-vremeni-k-arduino/
 *  https://www.pjrc.com/teensy/td_libs_Time.html
 *  https://www.pjrc.com/teensy/td_libs_DS1307RTC.html
 */

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

void setup() {
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");

//  setSyncProvider(RTC.get);   //Устанавливаем время в формате:
//  setTime(22,19,0,12,02,2017);   //Часы, минуты, секунды, день, месяц, год
//  RTC.set(now());   //Применяем:

}

void loop() {
  tmElements_t tm;

  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");  print2digits(tm.Hour);  Serial.write(':');  print2digits(tm.Minute);  Serial.write(':');  print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");  print2digits(tm.Day);  Serial.write('/');  print2digits(tm.Month);  Serial.write('/');  Serial.println(tm.Year+1970);  //tmYearToCalendar(tm.Year));
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");  Serial.println("example to initialize the time and begin running.");  Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");  Serial.println();
    }
    delay(9000);
  }
  delay(1000);

/*
 * 
 *  http://knodit.blogspot.com/2014/05/arduino-ds3231-i2c-wire.html - WIRE!!!!
 *  http://arduino-ua.com/docs/DS3231.pdf
 */
   Wire.beginTransmission(0x68); // 104 is DS3231 device address
   Wire.write(0x00); // start register
   Wire.endTransmission();
   Wire.requestFrom(0x68, 3); // request x bytes
  
   if(Wire.available()) {
     Serial.println(Wire.read() + Wire.read()*256 + Wire.read()*65536, HEX);
   }

}

void print2digits(int number) {
  if (number < 10) {    //  >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
