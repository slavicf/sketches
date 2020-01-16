/***************************************************

 ****************************************************/
//-----------------------------------------------------------------------

#define PS    2             // Кнопка давления
#define MODE  3             // Режим. 1 - ручной, 0 - автомат
#define START 4             // Кнопка старт
#define K1PB  5             // Кнопка К1
#define K2PB  6             // Кнопка К2 
#define K3PB  7             // Кнопка К3
#define K4PB  8             // Кнопка К4

#include <Button.h>
//-----------------------------------------------------------------------
//-----------------------------------------------------------------------
class Relay {
  const byte pin;
    
  public:
//----------------------------- Constructor ------------------------------------------
    Relay(byte attachTo) : pin(attachTo) {
      pinMode(pin, OUTPUT);
    }
//----------------------------- Get state ------------------------------------------
    bool getState() {
      return digitalRead(pin);
    }
//----------------------------- Set state ------------------------------------------
    void setState(bool state) {
      digitalWrite(pin, state);
    }
};
//-----------------------------------------------------------------------
Button pressureBt(2);
Button modeSw(3);
Button startBt(4);
Button k1Bt(5);
Button k2Bt(6);
Button k3Bt(7);
Button k4Bt(8);
//-----------------------------------------------------------------------
Relay k1(9);
Relay k2(10);
Relay k3(11);
Relay k4(12);
Relay k5(13);
//-----------------------------------------------------------------------
void setup() {
  
}
//-----------------------------------------------------------------------
void loop() {
  inputsUpdate();
  k5.setState(!k1.getState && !k2.getState && !k3.getState && !k4.getState)
  
}
//-----------------------------------------------------------------------
void inputsUpdate() {
  pressureBt.update();
  modeSw.update();
  startBt.update();
  k1Bt.update();
  k2Bt.update();
  k3Bt.update();
  k4Bt.update();
}
