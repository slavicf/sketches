
#define SerialTxControl 10   //RS485 управляющий контакт на arduino pin 10
#define RS485Transmit    HIGH
#define RS485Receive     LOW  

char buffer[100];

void setup(void) {
  Serial.begin(9600);
  pinMode(SerialTxControl, OUTPUT);  
  digitalWrite(SerialTxControl, RS485Transmit); 
  Serial.print("TEST");  
  delay(100); 
  //digitalWrite(SerialTxControl, RS485Receive);   
}
 
void loop(void) {
   
  int i=0;
  if(Serial.available()){delay(100);

    while( Serial.available() && i< 99) {
      buffer[i++] = Serial.read();
    }
    buffer[i++]='\0';
  }
  
  if(i>0) {
    delay(1000);
    //digitalWrite(SerialTxControl, RS485Transmit); 
    Serial.print(buffer); // Выводим что приняли с других устройств
    //digitalWrite(SerialTxControl, RS485Receive);   
  }
 
}
