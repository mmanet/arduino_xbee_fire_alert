#include <SoftwareSerial.h>
#define RxD 3
#define TxD 2

#include "DHT.h"
#define DHTPIN 4  
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

int sensorValue;
int pin8 = 8;
char a;

SoftwareSerial mySerial(RxD,TxD); // RX, TX

void setup() {
    Serial.begin(9600);
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);
    mySerial.begin(9600);

    pinMode(pin8, OUTPUT);
    
    Serial.println("DHTxx test!");
    dht.begin();
}
 
void loop() {
   int h = dht.readHumidity();
   int t = dht.readTemperature();
   sensorValue = analogRead(0);
   
   if (isnan(t) || isnan(h)) {
      Serial.println("Failed to read from DHT");
    } 
    else {
     if(mySerial.available())
     { 
        Serial.println("Ready");
        //mySerial.print("a");
        a = mySerial.read();
        Serial.println(a);
        if(a==0x61){
              mySerial.print("a");
              
              mySerial.print("h");
              mySerial.print(h, DEC);
              mySerial.print("t");
              mySerial.print(t, DEC);
              mySerial.print("s");
              mySerial.print(sensorValue, DEC);
              mySerial.print("z");
              Serial.print(h);
              Serial.print(" ");
              Serial.print(t);
              Serial.print(" ");
              Serial.print(sensorValue, DEC);
              Serial.println(" ppm");
              //delay(1000);
        }else if(a==0x62||a==0x63){ 
          while(1){
           if(mySerial.available()){
              a = mySerial.read();
              Serial.print(a); 
              if(a=='z') break;
            }
           }
         }
      }else{
       Serial.println("Not Ready"); 
      }
    }
    delay(500);
}

