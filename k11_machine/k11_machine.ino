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
//-----------------------------------------------------------------------
class Button {
  const byte pin;
  bool old_button_state = true;
  bool actual_button_state = true;
  unsigned long time_marker;    // time marker in milliseconds
  unsigned long debounce = 50;  // debounce time in milliseconds
    
  public:
//----------------------------- Constructor ------------------------------------------
    Button(byte attachTo) : pin(attachTo) {
      pinMode(pin, INPUT_PULLUP);
      time_marker = millis();
    }
//----------------------------- Update state ------------------------------------------
    void update() {
      old_button_state = actual_button_state;
      bool b_state = digitalRead(pin);
      unsigned long ul_time = millis();
      if (b_state) {
        time_marker = ul_time;
        actual_button_state = false;
      } else if (ul_time - time_marker > debounce){
        actual_button_state = true;
      }
    }
//----------------------------- Get state ------------------------------------------
    bool getState() {
      return actual_button_state;
    }
//----------------------------- Get positive edge ------------------------------------------
    bool getPos() {
      return actual_button_state && !old_button_state;
    }
//----------------------------- Get negative edge ------------------------------------------
    bool getNeg() {
      return !actual_button_state && old_button_state;
    }
};
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
