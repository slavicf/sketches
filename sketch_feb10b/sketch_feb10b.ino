/*  http://arduino-project.net/podklyuchenie-ul-trazvukovogo-dal-nomera-hc-sr04-k-arduino/
 *  http://amperka.ru/product/hc-sr04-ultrasonic-sensor-distance-module
 *  http://smart-home.te.ua/arduino-datchyk-hc-sr04-ultrazvukovoj-dalnomer/
 *  
 *  Подключение ультразвукового дальномера HC-SR04
 */

#define echoPin 9
#define trigPin 8
#define pwm 5       // Выход ШИМ подключен к Digital 5

int duration, cm, pwm_data;   // переменная ШИМ
 
void setup() { 
  Serial.begin (9600); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(pwm, OUTPUT); // настроить пин мосфета как выход
} 
 
void loop() { 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH); 
  cm = duration / 58;
  Serial.print(cm); 
  Serial.println(" cm "); 
  
  pwm_data = map(duration, 100, 1000, 255, 0);
  if (pwm_data <0){
    pwm_data = 0;
  }
  analogWrite(pwm, pwm_data);  //pwm_data); // подать на мосфет ШИМ сигнал
  
  delay(100);
}
