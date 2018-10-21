/*
  Arduino the Object Oriented way
  http://paulmurraycbr.github.io/ArduinoTheOOWay.html
*/

#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>

#define SENSOR_0  10
#define SENSOR_1  11
#define LEVEL_MIN 0
#define LEVEL_MAX 127
#define PERIOD 1000 / 4 // period of timer in ms
#define SHINE 10 * 1000  // time of shining in ms

#define PIXEL_COUNT 16
#define PIXEL_PIN 12  // Digital IO pin connected to the NeoPixels.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

//  Detect negative and positive edges
class Edge {
    bool neg = false;
    bool pos = false;
    bool oldState = false;

  public:
    void detect(bool state) {
      neg = state && !oldState; // detect negative edge
      pos = !state && oldState; // detect positive edge
      oldState = state;         // store old value
    }

    bool getNeg() {
      return neg;
    }

    bool getPos() {
      return pos;
    }
};

class Input {
    const byte pin;

  public:
    Input(byte attachTo) :
      pin(attachTo)
    {
    }

    void setup() {
      pinMode(pin, INPUT);
    }

    bool getState() {
      return digitalRead(pin);
    }
};

class NeoPixel {
    long level = 0;
    unsigned long oldMs = 0;

  public:
    void shine(bool dir) {
      if (millis() - oldMs >= PERIOD) {
        changeLevel(dir);

        uint32_t color = level + (level << 8) + (level << 16);
        for (uint16_t i = 0; i < PIXEL_COUNT; i++) {
          strip.setPixelColor(i, color);
        }
        strip.show();

        oldMs = millis();
      }
    }

    void changeLevel(bool dir) {
      if (dir) level++;
      else level--;
      if (level < LEVEL_MIN) level = LEVEL_MIN;
      if (level > LEVEL_MAX) level = LEVEL_MAX;
    }
};

DetectEdge sensor();
Input sensor0(SENSOR_0);
Input sensor1(SENSOR_1);

void setup() {
  sensor0.setup();
  sensor1.setup();
  pinMode(LED_BUILTIN, OUTPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //  Serial.begin(9600);
  //  Serial.print("Level: ");
}

void loop() {

}

// WS2812 driver
void levels() {



  //  Serial.println(level);

}

