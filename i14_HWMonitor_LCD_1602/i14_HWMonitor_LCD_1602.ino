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
#define INT_PER 500000          // interrupt period in us
#define P1S   0        #define P2S   P1S  + 1 #define P4S   P2S  + 1 #define P8S   P4S  + 1
#define P16S  P8S  + 1 #define P32S  P16S + 1 #define P64S  P32S + 1 #define P128S P64S + 1

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3f, 16, 2);

byte phase;
TimeElements tm;
float fTemperature, fHumidity;

char inData[82];       // массив входных значений (СИМВОЛЫ)
int PCdata[20];        // массив численных значений показаний с компьютера
int &tCPU = PCdata[0]; int &tGPU  = PCdata[1];
int &tMB  = PCdata[2]; int &tHDD  = PCdata[3];
int &uCPU = PCdata[4]; int &uGPU  = PCdata[5];
int &uRAM = PCdata[6]; int &uGRAM = PCdata[7];
byte index = 0;
String string_convert;
unsigned long ulTimeout;
boolean bReadDHT22, bReadTime, bUpdateDisplay, bTimeOut;
