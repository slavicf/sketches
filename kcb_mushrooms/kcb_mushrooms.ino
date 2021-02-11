
#define DHT0   11     // DHT sensor
#define DHT1   12     // DHT sensor

#define D0_CLK  2   // Display
#define D0_DIO  3   // Display
#define D1_DIO  4   // Display

#define ENC_CLK 8   // Encoder
#define ENC_DT  9   // Encoder
#define ENC_SW 10   // Encoder

//#define SER     10   // Outputs Serial
//#define SRCLK   11   // Outputs Shift
//#define RCLK    12   // Outputs Storage
//#define OE      13   // Outputs Enable

#include "DHT.h"
#include "GyverTM1637.h"
#include "GyverEncoder.h"
#include <EEPROM.h>
#include "PCF8574.h"

DHT dht[] = { DHT(DHT0, DHT22), DHT(DHT1, DHT22) };
GyverTM1637 disp[] = { GyverTM1637( D0_CLK, D0_DIO), GyverTM1637( D0_CLK, D1_DIO) };
Encoder enc1(ENC_CLK, ENC_DT, ENC_SW, TYPE2);
PCF8574 expander(0x27);

//class   Chamber {
//  DHT         dht   (DHTPIN, DHTTYPE);
//  GyverTM1637 disp  (CLK, DIO);
//  int   temp;
//  int   hum;
//  int   par[6];   // sp_t, sp_h, f0_mode, f1_mode, hu_mode, he_mode
//  int   save;     // just for safe storage in mLevel4
//}

//void (*menuLevel[])() { menuLevel0, menuLevel1, menuLevel2, menuLevel3, menuLevel4 };   // https://forum.arduino.cc/index.php?topic=446798.0    https://arduino.stackexchange.com/questions/35516/help-with-struct-variable

struct  chamber { int temp;  int hum;  int par[8];  int save;  int a[4];  };  //struct  params {  int sp_t;    int sp_h;    byte f0_mode;    byte f1_mode;    byte hu_mode;    byte he_mode;  };
chamber chamber[2];
struct  sens  { int temp; int hum; };
sens    sensor[2];

char  mLevel = 0;
char  mItem[4];
unsigned long mTimer = 0;
unsigned long mCycle = 16000;

uint8_t mBuf[][4]    = { {_t, 0, 0, 0}, {_h, 0, 0, 0}, {_t, _b, 0, 0}, {_h, _b, 0, 0}, {_F, _0, 0, 0}, {_F, _1, 0, 0}, {_H, _U, 0, 0}, {_H, _E, 0, 0}, {_S, _A, _U, _E}, {_r, _E, _t, 0}  };
uint8_t sBuf[][2][4] = { { {0, 0, 0, _degree}, {0, 0, 0, _h} }, { {0, 0, 0, _degree}, {0, 0, 0, _h} } };

#define sensV mItem[0]
#define activ mItem[1]
#define item2 mItem[2]
#define item3 mItem[3]

byte  hysteresis = 10;
byte  phase = 0;
unsigned long pTimer = 0;
unsigned long pCycle = 100;

void setup() {  // ------------------------------------------------------------------

//  pinMode(SER, OUTPUT);
//  pinMode(SRCLK, OUTPUT);
//  pinMode(RCLK, OUTPUT);
//  outputs();
//  pinMode(OE, OUTPUT);

  Serial.begin(9600);

  dht[0].begin();
  dht[1].begin();

  EEPROM.get(0, chamber[0].par);
  EEPROM.get(16, chamber[1].par);
//  printEEPROM();

  expander.begin();

//    disp[0].clear();
    disp[0].point(true);
    disp[0].brightness(0);
//    disp[1].clear();
    disp[1].point(true);
    disp[1].brightness(0);

} // ------------------------------------------------------------------

void loop() {
  service();
} // ------------------------------------------------------------------
