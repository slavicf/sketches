/***************************************************
  TODO
  - Volume buttons
  - Degree
  - Percent
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Sensirion.h>

const uint8_t dataPin  =  2;  // SHT7x Data pin
const uint8_t clockPin =  3;  // SHT7x Clock pin
const uint8_t busyPin  =  4;  // DFPlayer Busy pin
const uint8_t sensorPin = 5;  // PIR Sensor HC-SR501
const uint8_t ssRXPin  =  10; // SoftwareSerial RX pin. Connected to DFPlayer TX pin 3
const uint8_t ssTXPin  =  11; // SoftwareSerial TX pin. Connected to DFPlayer RX pin 2
//const uint8_t volume   =  25; // DFPlayer Volume constant

float temperature;    // SHT7x Temperature variable
float humidity;       // SHT7x Humidity variable
float dewpoint;       // SHT7x DewPoint variable

int buf[32];          // buffer to play
int bufHead = 0;      // buffer head
int bufTail = 0;      // buffer tail

//int DFP_State;        // DFPlayer State
//int old_State;        // DFPlayer old (previos) State

bool playReq = false; // play request
bool playing = false; // playing now
bool firstCycle = true;
bool sensor = true;
bool sensorOld = true;


unsigned long timer = millis();
//unsigned long timer2 = millis();

Sensirion tempSensor = Sensirion(dataPin, clockPin);  // SHT7x Initialization
SoftwareSerial mySoftwareSerial(ssRXPin, ssTXPin);    // SoftwareSerial Initialization
DFRobotDFPlayerMini myDFPlayer;                       // DFPlayer Initialization
//void printDetail(uint8_t type, int value);

void setup() {
  pinMode(busyPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);

  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  
  if (!myDFPlayer.begin(mySoftwareSerial, false)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
  }
  Serial.println(F("DFPlayer Mini online."));
  
//  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
//  myDFPlayer.play(1);  //Play the first mp3
//  myDFPlayer.playFolder(1, 90);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
}
