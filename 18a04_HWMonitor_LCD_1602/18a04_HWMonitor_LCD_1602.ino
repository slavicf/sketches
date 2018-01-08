//-----------------------------------------------------------------------
#include <Wire.h>               //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
#include "DHT.h"
#include <LiquidCrystal_I2C.h>  // библиотека дисплея
#include <DS3232RTC.h>          // http://github.com/JChristensen/DS3232RTC
#include <TimeLib.h>            // http://www.arduino.cc/playground/Code/Time
#include <TimerOne.h>           // библиотека таймера https://playground.arduino.cc/Code/Timer1
//-----------------------------------------------------------------------
#define DHTPIN 9                // what digital pin we're connected to
#define DHTTYPE DHT22           // DHT 22  (AM2302), AM2321
#define timerPeriod 500000             // timer1, and set a 1/2 second period

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3f, 16, 2);

byte phase;
//time_t t;
TimeElements tm;
float fTemperature, fHumidity;

char inData[82];       // массив входных значений (СИМВОЛЫ)
int PCdata[20];        // массив численных значений показаний с компьютера
                       // [0] - CPU temperature, [1] - GPU temperature
                       // [2] - MB temperature,  [3] - HDD temperature
                       // [4] - CPU usage,       [5] - FPU usage
                       // [6] - CPU RAM usage,   [7] - GPU RAM usage
byte index = 0;
String string_convert;
unsigned long ulTimeout;
boolean bReadDHT22, bReadTime, bUpdateDisplay, bTimeOut;

