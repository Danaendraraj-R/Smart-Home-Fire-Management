#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLVVcT0rc1"
#define BLYNK_TEMPLATE_NAME "INDUSTRIAL MONITORING"
#define BLYNK_AUTH_TOKEN "GnSTVNjuUEBBkVaZdRPBqhkysSU10LQ1"
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IOT";
char pass[] = "123456789";
char auth[] = BLYNK_AUTH_TOKEN;
unsigned int m=0,act=0,val,val1,val2,val3,val4,val5;

String inputString = ""; 
unsigned char a[200];

void setup()
{
  Serial.begin(9600);
  
   Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  
}

void loop()
{
  
  
   while(Serial.available())
    {
        char data;
        data=Serial.read();
  
        a[m]=data;
          if(a[0] == '*')
          {
            if(m<=12)
            {m++;}
          }
      }
      if(m > 1)
      {
        val = (a[1]-0x30)*100 + (a[2]-0x30)*10  + (a[3] - 0x30);
        val1 = (a[4]-0x30)*100 + (a[5]-0x30)*10  + (a[6] - 0x30);
        val2 = (a[7]-0x30)*100 + (a[8]-0x30)*10  + (a[9] - 0x30);
        val3 = (a[10]-0x30)*100 + (a[11]-0x30)*10  + (a[12] - 0x30);
        
    
        m=0;
      }
     
      Blynk.virtualWrite(V0,val);
      
      delay(100);
      Blynk.virtualWrite(V1,val1);
      
      delay(100);
      Blynk.virtualWrite(V2,val2);
      delay(100);
      if(val2>=20){SendMessage1();SendMessage3();Blynk.virtualWrite(V4,"SMOKE DETECTED ");}
      Blynk.virtualWrite(V3,val3);
      delay(100);
     if(val3==1){SendMessage();SendMessage2();Blynk.virtualWrite(V4,"FIRE DETECTED ");}
    
      Blynk.run();
      delay(100);
}
void SendMessage()

{

Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(2000);  // Delay of 1000 milli seconds or 1 second

 Serial.println("AT+CMGS=\"+919095057479\"\r"); // Replace x with mobile number

  delay(2000);

       Serial.println("FIRE DETECTED ");// The SMS text you want to send
           Serial.print("TEMPERATURE : ");
          Serial.println(val);
            Serial.print("HUMIDITY : ");
          Serial.println(val1);
          Serial.print("SMOKE : ");
          Serial.println(val2);
          delay(100);

  Serial.println((char)26);// ASCII code of CTRL+Z

  delay(2000);

}
void SendMessage1()

{

Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(2000);  // Delay of 1000 milli seconds or 1 second

 Serial.println("AT+CMGS=\"+919095057479\"\r"); // Replace x with mobile number

  delay(2000);

       Serial.println("SMOKE DETECTED ");// The SMS text you want to send
           Serial.print("TEMPERATURE : ");
          Serial.println(val);
            Serial.print("HUMIDITY : ");
          Serial.println(val1);
          Serial.print("SMOKE : ");
          Serial.println(val2);
           Serial.print("FIRE : ");
          Serial.println(val3);
          delay(100);

  Serial.println((char)26);// ASCII code of CTRL+Z

  delay(2000);

}
void SendMessage2()

{

Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(2000);  // Delay of 1000 milli seconds or 1 second

 Serial.println("AT+CMGS=\"+919347534114\"\r"); // Replace x with mobile number

  delay(2000);

       Serial.println("FIRE DETECTED ");// The SMS text you want to send
           Serial.print("TEMPERATURE : ");
          Serial.println(val);
            Serial.print("HUMIDITY : ");
          Serial.println(val1);
          Serial.print("SMOKE : ");
          Serial.println(val2);
          delay(100);

  Serial.println((char)26);// ASCII code of CTRL+Z

  delay(2000);

}
void SendMessage3()

{

Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

  delay(2000);  // Delay of 1000 milli seconds or 1 second

 Serial.println("AT+CMGS=\"+918328540919\"\r"); // Replace x with mobile number

  delay(2000);

       Serial.println("SMOKE DETECTED ");// The SMS text you want to send
           Serial.print("TEMPERATURE : ");
          Serial.println(val);
            Serial.print("HUMIDITY : ");
          Serial.println(val1);
          Serial.print("SMOKE : ");
          Serial.println(val2);
           Serial.print("FIRE : ");
          Serial.println(val3);
          delay(100);

  Serial.println((char)26);// ASCII code of CTRL+Z

  delay(2000);

}