
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

//struct  params {  int sp_t;    int sp_h;    byte f0_mode;    byte f1_mode;    byte hu_mode;    byte he_mode;  };
struct  chamber {  int temp;  int hum;  int par[6];  int save;  int a[6];  };
chamber chamber[2];

char  menuLevel;
int  menuItem[4];
//  uint8_t bright = 0;

uint8_t L0Buffer[][4] = { {0, 0, 0, _degree}, {0, 0, 0, _H}, {0, 0, 0, _degree}, {0, 0, 0, _H}, };
uint8_t L2Buffer[][4] = { {_S, _P, _empty, _t}, {_S, _P, _empty, _H}, {_F, _0, _empty, _empty}, {_F, _1, _empty, _empty},
                         {_H, _U, _empty, _empty}, {_H, _E, _A, _t}, {_S, _A, _U, _E}, {_empty, _r, _E, _t}  };

byte  hysteresis = 10;
byte  phase = 0;
unsigned long pTimer = 0;
unsigned long pCycle = 100;
unsigned long mTimer = 0;
unsigned long mCycle = 16000;

uint8_t output = 0;

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
  EEPROM.get(12, chamber[1].par);
  printEEPROM();

  expander.begin();

  //  disp0.clear();
  //  disp1.clear();
  //  disp0.point(true);
  //  disp1.point(true);
  //  setBright(bright, bright);

} // ------------------------------------------------------------------

void loop() {
  service();
} // ------------------------------------------------------------------