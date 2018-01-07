//-----------------------------------------------------------------------
#include "DHT.h"
#include <LiquidCrystal_I2C.h>  // библиотека дисплея
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
//#include <Time.h>         //http://www.arduino.cc/playground/Code/Time
#include <TimeLib.h>
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
//-----------------------------------------------------------------------
#define DHTPIN 9                // what digital pin we're connected to
#define DHTTYPE DHT22           // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3f, 16, 2);

String sDate, sTime;
float temp, hum;
//-------  стартовый логотип AlexGyver ----------------------------------
byte char1[8] = {0b00011, 0b00110, 0b01110, 0b11111, 0b11011, 0b11001, 0b00000, 0b00000};
byte char2[8] = {0b10000, 0b00001, 0b00001, 0b00001, 0b00000, 0b10001, 0b11011, 0b11111};
byte char3[8] = {0b11100, 0b11000, 0b10001, 0b11011, 0b11111, 0b11100, 0b00000, 0b00000};
byte char4[8] = {0b00000, 0b00001, 0b00011, 0b00111, 0b01101, 0b00111, 0b00010, 0b00000};
byte char5[8] = {0b11111, 0b11111, 0b11011, 0b10001, 0b00000, 0b00000, 0b00000, 0b00000};
byte char6[8] = {0b00000, 0b10000, 0b11000, 0b11100, 0b11110, 0b11100, 0b01000, 0b00000};
//-------  значок градуса ----------------------------------
byte degree[8] = {0b01000, 0b10100, 0b01000, 0b00110, 0b01001, 0b01000, 0b01001, 0b00110};
//-----------------------------------------------------------------------
char logo0[4] = {1, 2, 3};
char logo1[4] = {4, 5, 6};

char inData[82];       // массив входных значений (СИМВОЛЫ)
int PCdata[20];        // массив численных значений показаний с компьютера
byte index = 0;
String string_convert;
unsigned long timeout;
boolean updateDisplay_flag, timeOut_flag = 1;

