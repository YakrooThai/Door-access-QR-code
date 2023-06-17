#include <HardwareSerial.h>
HardwareSerial SerialPort2(2); // use UART2

char number  = ' ';
int LED = 2;
int REY = 23;
void setup()
{
  Serial.begin(9600);
  SerialPort2.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(LED, OUTPUT);
  pinMode(REY, OUTPUT);
  Serial.println("\r\n//====================================//");
  Serial.println("          QR code access control ");
  Serial.println("//====================================//");

}

int8_t getQR(unsigned int timeout)
{
    uint8_t x=0,  answer=0,i;
    char res[30];
    unsigned long pre;
    Serial.println("Wait QR..(3 Sec).");

    while( Serial.available() > 0) Serial.read();   
    x = 0;
    pre = millis();
    do{
        if(SerialPort2.available() != 0){    
            res[x] = SerialPort2.read();
            x++;
            
            if ((res[x-1]=='4')&&(res[x-2]=='3')&&(res[x-3]=='2')&&(res[x-4]=='1')) //password
            {
                answer = 1;
            }
        }
    }
    while((answer == 0) && ((millis() - pre) < timeout));    
    return answer;
}
void loop()
{
  int answer ;
  answer = getQR(3000);
   if (answer == 1)
   {  
      answer =0;    
      Serial.println("OK Open DOOR");
      digitalWrite(REY,HIGH);
      delay(1000);
      delay(1000);
      delay(1000);
      Serial.println(">> OFF DOOR");
      digitalWrite(REY, LOW);
      delay(1000);
      delay(1000);
      delay(1000);

  }
}
