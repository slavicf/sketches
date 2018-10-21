/* http://geekmatic.in.ua/arduino_otobrazhenie_dannyih_float
 * sprintf не работает с float
 * надо использовать dtostrf
 */
float num = 15.25;
char msg[128];
void setup()
{
Serial.begin(9600);
}
void loop()
{
  sprintf(msg, "%02.1f", num);
  dtostrf(num, 7, 2, msg);
  Serial.println(msg);
  delay(100);
}
