/***************************************************
  ATtiny85 Christmas Light Controller
  Р0 ~ ARef, I²C SDA
  P1 ~ LED
  P2 - ADC1, I²C SCK
  P3 - ADC3, USB+
  P4 ~ ADC2, USB-
  P5 - ADC0
  
  TODO:
  - Relay
  - Case
 ****************************************************/
//-----------------------------------------------------------------------
#define OUT 0             // Relay out
#define LED 1             // LED out
#define PV  1             // Process Value on AI 1 (P2)
#define SP  2             // SetPoint on AI 2 (P4)
#define HYS 24            // Hysteresis 0-32 as 0-100%
#define DEBOUNCE 1000 * 2 // Debounce time in milliseconds
unsigned long timer;

void setup() {
  pinMode(OUT, OUTPUT);
}

void loop() {
  
  int pv = analogRead(PV);
  int sp = analogRead(SP);
  int spLo = (sp * HYS) >> 5;
  
  if (pv < spLo) {
    digitalWrite(OUT, HIGH);
    digitalWrite(LED, HIGH);
    timer = millis();
  }
  
  if (pv > sp) {
    digitalWrite(LED, LOW);
    if (millis() - timer > DEBOUNCE) {
      digitalWrite(OUT, LOW);
    }
  }
  
}
