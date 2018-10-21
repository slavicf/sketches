/*   http://pikabu.ru/story/distantsionnoe_plavnoe_upravlenie_svetom_i_servoprivodom_na_arduino_4716361
 *   https://www.youtube.com/watch?v=p0v2vSmajx8&feature=youtu.be
 *   http://cxem.net/arduino/arduino68.php
 *   http://zelectro.cc/joystick_Arduino
 *   
 *   Показывает работу с:
 *   - джойстиком
 *   - аналоговыми входами
 *   - дискретными входами/выходами
 *   - серийным портом
*/

// i/o
#define axis_X 0    // Ось Х подключена к Analog 0
#define axis_Y 1    // Ось Y подключена к Analog 1
#define axis_Z 4    // Ось Z (кнопка джойстика) подключена к Digital 4
#define pwm 5       // Выход ШИМ подключен к Digital 5

int value_X, value_Y, value_Z = 0;    // Переменные для хранения значений осей

byte JoyRx;  //  Значение оси Х
byte JoyRy;  //  Значение оси У
byte pwm_data;   // переменная ШИМ


void setup() {
  pinMode(axis_Z, INPUT_PULLUP);
  pinMode(pwm, OUTPUT); // настроить пин мосфета как выход
  Serial.begin(9600);
}

void loop() {

  value_X = analogRead(axis_X);    // Считываем аналоговое значение оси Х
  Serial.print(" X:");
  Serial.print(value_X, DEC);      // Выводим значение в Serial Monitor
 
  value_Y = analogRead(axis_Y);    // Считываем аналоговое значение оси Y
  Serial.print(" | Y:");
  Serial.print(value_Y, DEC);      // Выводим значение в Serial Monitor
 
  value_Z = !digitalRead(axis_Z);   // Считываем цифровое значение оси Z (кнопка)
  //  value_Z = value_Z ^ 1;           // Инвертируем значение
  Serial.print(" | Z: ");
  Serial.println(value_Z, DEC);    // Выводим значение в Serial Monitor

  if (value_Z){
    pwm_data = 255;
  } else {
    pwm_data = map(value_X, 0, 1023, 0, 255);
  }
  analogWrite(pwm, pwm_data); // подать на мосфет ШИМ сигнал
  delay(100);
}

