/***************************************************
  TODO
  - 
 ****************************************************/
//-----------------------------------------------------------------------
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "Sensirion.h"
//-----------------------------------------------------------------------
#define SHT_DATA   7  // SHT7x Data pin
#define SHT_CLOCK  8  // SHT7x Clock pin
#define PIR_SENSOR 9  // PIR Sensor HC-SR501
#define SS_RX     10  // SoftwareSerial RX pin. Connected to DFPlayer TX pin 3
#define SS_TX     11  // SoftwareSerial TX pin. Connected to DFPlayer RX pin 2
#define DFP_BUSY  12  // DFPlayer Busy pin
//-----------------------------------------------------------------------
Sensirion tempSensor = Sensirion(SHT_DATA, SHT_CLOCK);  // SHT7x Initialization
DFRobotDFPlayerMini myDFPlayer;                       // DFPlayer Initialization
SoftwareSerial mySoftwareSerial(SS_RX, SS_TX);    // SoftwareSerial Initialization
//-----------------------------------------------------------------------
class Sensor {
    const byte pin;
    bool actual = false;
    bool old = false;

  public:
    Sensor(byte attachTo) :
      pin(attachTo)
    {
      pinMode(pin, INPUT);
    }

    bool update() {
      old = actual;
      actual = digitalRead(pin);
      return actual;
    }

    bool getState() {
      return actual;
    }

    bool pos() {
      return actual && !old;
    }
};

Sensor sensor(PIR_SENSOR);
//-----------------------------------------------------------------------
/*** Class FIFO Buffer ******************************/
class Buffer {
  int buf[32];          // buffer to play
  int head = 0;      // buffer head
  int tail = 0;      // buffer tail

  public:
    bool push(int value) {
      int temp = (head + 1) & 0x1F;
      if(temp != tail) {
        head = temp;
        buf[head] = value;
        return true;
      } else {
        return false;
      }
    }

    int pull() {
      if(!empty()) {
        tail = ++tail & 0x1F;
        return buf[tail];
      } else {
        return -1;
      }
    }

    bool empty() {
      return head == tail;
    }

};

Buffer buf;

void setup() {
  pinMode(DFP_BUSY, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  
  if (!myDFPlayer.begin(mySoftwareSerial, false)) {  //Use softwareSerial to communicate with mp3.
    Serial.println("Unable to begin:");
    Serial.println("1.Please recheck the connection!");
    Serial.println("2.Please insert the SD card!");
  }
  Serial.println("DFPlayer Mini online.");
  delay(5000);  // PIR Sensor calibration delay
  Serial.println("Start working");
  
//  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
//  myDFPlayer.play(1);  //Play the first mp3
//  myDFPlayer.playFolder(1, 90);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
}
