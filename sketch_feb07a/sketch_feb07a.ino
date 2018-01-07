/*
http://www.prorobot.ru/arduino/nano-v3.php
Мигание светодиодом SOS.
Слегка модифицированный стандартный скетч мигания светодиодом. 
Имитирует сигнал SOS азбуки Морзе, повторяя поочередно три коротких вспышки,
три длинных, затем опять три коротких.
Подробнее сдесь http://www.craft-tech.ru
 */


// Скетч включается при подаче питания, либо при нажатии кнопки reset
void setup() {
  pinMode(13, OUTPUT);  // работаем с 13 пином.
}

// функция loop запускает скетч по кругу
void loop() {
  digitalWrite(13, HIGH); // подает напряжение на 13 ноку светодиода
  delay(100);      // ждем 1 десятую секунды
  digitalWrite(13, LOW);  // выключаем напряжение с 13 ноги
  delay(100); 
  digitalWrite(13, HIGH); 
  delay(100);      
  digitalWrite(13, LOW);  
  delay(100); 
  digitalWrite(13, HIGH); 
  delay(100);      
  digitalWrite(13, LOW);  
  delay(200);      // ждем 2 десятые секунды
  digitalWrite(13, HIGH);  // включаем напряжение
  delay(500);      // ждем пол секунды
  digitalWrite(13, LOW);  // выключаем напряжение
  delay(100); 
  digitalWrite(13, HIGH); 
  delay(500);      
  digitalWrite(13, LOW);  
  delay(100); 
  digitalWrite(13, HIGH); 
  delay(500);      
  digitalWrite(13, LOW);  
  delay(200);
  digitalWrite(13, HIGH); // и опять короткие вспышки
  delay(100);      
  digitalWrite(13, LOW);  
  delay(100); 
  digitalWrite(13, HIGH); 
  delay(100);      
  digitalWrite(13, LOW); 
  delay(100); 
  digitalWrite(13, HIGH); 
  delay(100);     
  digitalWrite(13, LOW); 
  delay(2000);      // ждем 6 секунд и все повторяется заново
}
