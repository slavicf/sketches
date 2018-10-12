#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>

#define SENSOR_0  10
#define SENSOR_1  11
#define LEVEL_MIN 0
#define LEVEL_MAX 127
#define PERIOD 1000 * 1000 / 4 // period of timer in us
#define SHINE 10 * 1000  // time of shining in ms

#define PIXEL_COUNT 16
#define PIXEL_PIN 12  // Digital IO pin connected to the NeoPixels.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

long level = 0;
boolean dir = true;
boolean sensor;
byte tic = 0;
boolean ticBit[8] = {0, 0, 0, 0, 0, 0, 0, 0};
boolean ticBit1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned long timer[4] = {0, 0, 0, 0};
boolean timer0;

void setup() {
  Timer1.initialize(PERIOD); // initialize timer
  Timer1.attachInterrupt(timerTic); // attach the service routine here
  pinMode(SENSOR_0, INPUT);
  pinMode(SENSOR_1, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //  Serial.begin(9600);
}

void loop() {
  timeBits(); // setting positive edges
  sensor = digitalRead(SENSOR_0) || digitalRead(SENSOR_1);
  if (sensor) {
    timer[0] = millis() + SHINE;
  }
  timer0 = millis() < timer[0];
  digitalWrite(LED_BUILTIN, sensor);

  if (ticBit[0]) {
    levels();
  }
}

// timer interrupt
void timerTic() {
  tic++;
}

// setting positive edges
void timeBits() {
  for (int i = 0; i < 8; i++) {
    if (bitRead(tic, i)) {
      if (!ticBit1[i]) {
        ticBit[i] = true;
        ticBit1[i] = true;
      } else ticBit[i] = false;
    } else {
      ticBit[i] = false;
      ticBit1[i] = false;
    }
  }
}

