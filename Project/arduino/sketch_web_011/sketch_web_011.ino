#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>
#define RxD 3
#define TxD 2
SoftwareSerial mySerial(RxD,TxD); // RX, TX

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(31,170,167,148);  // ใช้ในกรณีเป็น IP
//char server[] = "www.google.com";    // ใช้ในกรณีเป็น Domain

IPAddress ip(192,168,1,8); // IP ของ Arduino
EthernetClient client;

//float temp=0;

int status1=0;
int istep=0,istep2=0,istep3=0;
String s[3];
String s2[3];
String s3[3];
String temp,humidity,smoke;
String temp2,humidity2,smoke2;
String temp3,humidity3,smoke3;
String tempa,humiditya,smokea;
String tempa2,humiditya2,smokea2;
String tempa3,humiditya3,smokea3;
int id=1,id2=1,id3=1,id4=1;
int mid=0;
char a;
int tempp=0,tempp2=0,tempp3=0;
int tempn=0,tempn2=0,tempn3=0;
int chw=0,chw2=0,chw3=0;

void setup() {
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  mySerial.begin(9600);
  mySerial.flush();
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
  delay(1000);
  Serial.println("connecting...");
}

void loop()
{
    xbeeall();
    //delay(3000);
}

void xbeeall()
{
    temp = "";
    humidity = "";
    smoke = "";
    
    temp2 = "";
    humidity2 = "";
    smoke2 = "";

    temp3 = "";
    humidity3 = "";
    smoke3 = "";
    
    if(status1==0){
      mySerial.print("a");
      delay(1000);
      status1=1;
    }
    else if(status1==2){
      mySerial.print("b");
      delay(1000);
      status1=3;
    }
    else if(status1==4){
      mySerial.print("c");
      delay(1000);
      status1=5;
    }
    
  if(mySerial.available()){
     a = mySerial.read();
     Serial.print(a);
     
     if(status1==1&&a=='a'){
     }else if(status1==1&&(a=='a'||a=='t'||a=='s')){
          istep++;
     }else if(status1==1&&a!='z'){
        if(a!='h'&&status1!=2&&status1!=4){
          s[istep] += a;
        }
     }
        
     if(status1==1&&a=='z'){
        status1=2;
     }
     if(status1==2&&a=='z'){
        Serial.println();
        Serial.println("Data A");
        Serial.print("Debug [h]:"+s[0]);
        Serial.print(" Debug [t]:"+s[1]);
        Serial.println(" Debug [s]:"+s[2]);
        humidity = s[0];
        temp = s[1];
        smoke = s[2];

        humiditya = s[0];
        tempa = s[1];
        smokea = s[2];

        tempp=temp.toInt();
        tempp=tempn;
        tempn=temp.toInt();
        
        if(tempn>=tempp+5&&chw==1){
          mid=1;
          web4();
        }else{
          web1();
          chw=1;
        }
        
        s[0]=s[1]=s[2]="";
        status1=2;
        istep=0;
        istep2=0;
        istep3=0;
     }else{
     
       if(status1==3&&a=='b'){
       }else if(status1==3&&(a=='b'||a=='t'||a=='s')){
            istep2++;
       }else if(status1==3&&a!='z'){
            if(a!='h'){
              s2[istep2] += a;
            }
       }
  
       else if(status1==3&&a=='z'){
          Serial.println();
          Serial.println("Data B");
          Serial.print("Debug B [h]:"+s2[0]);
          Serial.print(" Debug B [t]:"+s2[1]);
          Serial.println(" Debug B [s]:"+s2[2]);
          humidity2 = s2[0];
          temp2 = s2[1];
          smoke2 = s2[2];

          humiditya2 = s2[0];
          tempa2 = s2[1];
          smokea2 = s2[2];
  
          tempp2=temp2.toInt();
          tempp2=tempn2;
          tempn2=temp2.toInt();
          
          if(tempn2>=tempp2+10&&chw2==1){
            mid=2;
            web5();
          }else{
            web2();
            chw2=1;
          }
          
          s2[0]=s2[1]=s2[2]="";
          status1=4;
          istep2=0;
          istep=0;
          istep3=0;
          a = 'c';
       }

         if(status1==5&&a=='c'){
         }else if(status1==5&&(a=='c'||a=='t'||a=='s')){
              istep3++;
         }else if(status1==5&&a!='z'){
              if(a!='h'){
                s3[istep3] += a;
              }
         }
         else if(status1==5&&a=='z'){
            Serial.println();
            Serial.println("Data C");
            Serial.print("Debug C [h]:"+s3[0]);
            Serial.print(" Debug C [t]:"+s3[1]);
            Serial.println(" Debug C [s]:"+s3[2]);

            humidity3 = s3[0];
            temp3 = s3[1];
            smoke3 = s3[2];
  
            humiditya3 = s3[0];
            tempa3 = s3[1];
            smokea3 = s3[2];
    
            tempp3=temp3.toInt();
            tempp3=tempn3;
            tempn3=temp3.toInt();
            
            if(tempn3>=tempp3+10&&chw3==1){
              mid=3;
              web6();
            }else{
              web3();
              chw3=1;
            }
            
            s3[0]=s3[1]=s3[2]="";
            status1=0;
            istep3=0;
            istep2=0;
            istep=0;
            a = 'a';
         }
     }
  }
}

void web1()
{
    if (client.connect(server, 80)) {
      Serial.println("connected");
      
      client.print("GET http://firetank.esy.es/temp_3.php?");
      client.print("machine=");
      client.print("1");
      client.print("&");
      client.print("n001_id=");
      if(id<=5){
        client.print(id);
        id++;
      }else{
        id=1;
      }
      client.print("&");
      client.print("n001_temp=");
      client.print(temp);
      client.print("&");
      client.print("n001_humidity=");
      client.print(humidity);
      client.print("&");
      client.print("n001_smoke=");
      client.print(smoke);
      client.println("HTTP/1.1");
      client.println("Connection: close");
      client.println();
  
      Serial.print("temp = ");
      
      Serial.println(temp);
      Serial.println(humidity);
      Serial.println(smoke);
    }
    else {
      Serial.println("connection failed");
    }
      client.stop();
      
}

void web2()
{
    if (client.connect(server, 80)) {
      Serial.println("connected");
      
      client.print("GET http://firetank.esy.es/temp_3.php?");
      client.print("machine2=");
      client.print("2");
      client.print("&");
      client.print("n002_id=");
      if(id2<=5){
        client.print(id2);
        id2++;
      }else{
        id2=1;
      }
      client.print("&");
      client.print("n002_temp=");
      client.print(temp2);
      client.print("&");
      client.print("n002_humidity=");
      client.print(humidity2);
      client.print("&");
      client.print("n002_smoke=");
      client.print(smoke2);
      client.println("HTTP/1.1");
      client.println("Connection: close");
      client.println();
  
      Serial.print("temp2 = ");
      
      Serial.println(temp2);
      Serial.println(humidity2);
      Serial.println(smoke2);
      //Serial.println(direction2);
    }
    else {
      Serial.println("connection failed");
    }
      client.stop();
      
}

void web3()
{
    if (client.connect(server, 80)) {
      Serial.println("connected");
      
      client.print("GET http://firetank.esy.es/temp_3.php?");
      client.print("machine3=");
      client.print("3");
      client.print("&");
      client.print("n003_id=");
      if(id3<=5){
        client.print(id3);
        id3++;
      }else{
        id3=1;
      }
      client.print("&");
      client.print("n003_temp=");
      client.print(temp3);
      client.print("&");
      client.print("n003_humidity=");
      client.print(humidity3);
      client.print("&");
      client.print("n003_smoke=");
      client.print(smoke3);
      //client.print("&machine=2");
      client.println("HTTP/1.1");
      client.println("Connection: close");
      client.println();
  
      Serial.print("temp3 = ");
      
      Serial.println(temp3);
      Serial.println(humidity3);
      Serial.println(smoke3);
    }
    else {
      Serial.println("connection failed");
    }
      client.stop();
      
}

void web4()
{
    if (client.connect(server, 80)) {
      Serial.println("connected");
      
      client.print("GET http://firetank.esy.es/alert_3.php?");
      client.print("alert_id=");
      if(id4<=5){
        client.print(id4);
        id4++;
      }else{
        id4=1;
      }
      client.print("&");
      client.print("machine_id=");
      client.print(mid);
      client.print("&");
      client.print("alert_temp=");
      client.print(tempa);
      client.print("&");
      client.print("alert_humidity=");
      client.print(humiditya);
      client.print("&");
      client.print("alert_smoke=");
      client.print(smokea);
      client.println("HTTP/1.1");
      client.println("Connection: close");
      client.println();
    }
    else {
      Serial.println("connection failed");
    }
      client.stop();
      
}

void web5()
{
    if (client.connect(server, 80)) {
      Serial.println("connected");
      
      client.print("GET http://firetank.esy.es/alert_3.php?");
      client.print("alert_id2=");
      if(id4<=5){
        client.print(id4);
        id4++;
      }else{
        id4=1;
      }
      client.print("&");
      client.print("machine_id2=");
      client.print(mid);
      client.print("&");
      client.print("alert_temp2=");
      client.print(tempa2);
      client.print("&");
      client.print("alert_humidity2=");
      client.print(humiditya2);
      client.print("&");
      client.print("alert_smoke2=");
      client.print(smokea2);
      client.println("HTTP/1.1");
      client.println("Connection: close");
      client.println();
    }
    else {
      Serial.println("connection failed");
    }
      client.stop();
      
}

void web6()
{
    if (client.connect(server, 80)) {
      Serial.println("connected");
      
      client.print("GET http://firetank.esy.es/alert_3.php?");
      client.print("alert_id3=");
      if(id4<=5){
        client.print(id4);
        id4++;
      }else{
        id4=1;
      }
      client.print("&");
      client.print("machine_id3=");
      client.print(mid);
      client.print("&");
      client.print("alert_temp3=");
      client.print(tempa3);
      client.print("&");
      client.print("alert_humidity3=");
      client.print(humiditya3);
      client.print("&");
      client.print("alert_smoke3=");
      client.print(smokea3);
      client.println("HTTP/1.1");
      client.println("Connection: close");
      client.println();
    }
    else {
      Serial.println("connection failed");
    }
      client.stop();
      
}

