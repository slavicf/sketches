
void setup() {
  Serial.begin(9600);
  Timer1.initialize(40);   // поставить частоту ШИМ 25 кГц (40 микросекунд)
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  digitalWrite(R_PIN, 0);
  digitalWrite(G_PIN, 0);
  digitalWrite(B_PIN, 0);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  sensors.begin();
  sensors.getAddress(Thermometer1, 0);
  sensors.getAddress(Thermometer2, 1);
  sensors.setResolution(Thermometer1, TEMPERATURE_PRECISION);
  sensors.setResolution(Thermometer2, TEMPERATURE_PRECISION);
  // инициализация дисплея
  lcd.init();
  lcd.backlight();
  lcd.clear();            // очистить дисплей
  show_logo();            // показать логотип
  delay(2000);
  lcd.clear();            // очистить дисплей
  show_logo2();            // показать логотип

  Timer1.pwm(FAN_PIN, 400);  // включить вентиляторы на 40%
  delay(2000);               // на 2 секунды
  lcd.clear();               // очистить дисплей
  PCdata[8] = speedMAX;
  PCdata[9] = speedMIN;
  PCdata[10] = tempMAX;
  PCdata[11] = tempMIN;
}
// 8-maxFAN, 9-minFAN, 10-maxTEMP, 11-minTEMP, 12-mnlFAN

