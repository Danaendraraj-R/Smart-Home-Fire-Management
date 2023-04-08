#include <Wire.h> 
#include <LCD_I2C.h>
LCD_I2C lcd(0x3F);
#include "DHT.h"
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define gas A3
#define relay 10
#define relay1 12
#define buzzer 4
#define fire A2
#define red 7
#define green 6
int t,h,gasv,firev;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 Wire.begin(); // gpio 2 and gpio 0 which are D4, and D3
  lcd.begin();                 //Init the LCD
  lcd.backlight();            //Activate backlight     
  lcd.home(); 
   lcd.setCursor(0,0);lcd.print("   INDUSTRIAL");
   lcd.setCursor(0,1);lcd.print("MOINTORING IOT");
  delay(2000);
  lcd.clear(); 
   dht.begin();
   pinMode(gas,INPUT);
   pinMode(fire,INPUT);
    pinMode(relay,OUTPUT);
  digitalWrite(relay,HIGH);
  pinMode(relay1,OUTPUT);
 digitalWrite(relay1,HIGH);
  pinMode(red,OUTPUT);
  digitalWrite(red,HIGH);
  pinMode(green,OUTPUT);
 digitalWrite(red,HIGH);
 pinMode(buzzer,OUTPUT);
 digitalWrite(buzzer,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
t = dht.readTemperature(); 
    lcd.setCursor(0,0);lcd.print("TEM:");
    if(t < 9){lcd.print("0");lcd.print(t);}
    else if(t < 99){lcd.print(t);}

  //to read humidity.....................................................

    h = dht.readHumidity();
    lcd.setCursor(8,0);lcd.print("HUM:");
    if(h < 9){lcd.print("0");lcd.print(h);}
    else if(h < 99){lcd.print(h);}

    gasv=analogRead(gas);
    gasv=map(gasv,0,900,0,100);
    lcd.setCursor(0,1);lcd.print("SMOKE:");
    if(gasv<0){gasv=0; }
    if(gasv <= 9){lcd.print("00");lcd.print(gasv);}
    else if(gasv <= 99){lcd.print("0");lcd.print(gasv); }
    else if(gasv <= 999){lcd.print(gasv);}
if(gasv>=20)
{
 lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("SMOKE DETECTED ");
    lcd.setCursor(0,1);
   lcd.print("           ");
   delay(1000);
    lcd.clear(); 
}

     if(digitalRead(fire)==LOW)
  {
    firev=1;
     digitalWrite(relay,LOW);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("FIRE DETECTED ");
    lcd.setCursor(0,1);
   lcd.print("           ");
   delay(1000);
    lcd.clear();
  }
  else
  {
     digitalWrite(relay,HIGH);
    firev=0;
  }
  if(gasv>=20||firev==1)
  {
    digitalWrite(buzzer,HIGH); 
  }
  else
  {
     digitalWrite(buzzer,LOW);
  }
  if(gasv>=20||t>=40)
{
  digitalWrite(relay1,LOW);
}
 else
 {
  digitalWrite(relay1,HIGH); 
 }
  if(gasv>=20||firev==1||t>=40)
  {
     digitalWrite(red,HIGH);
      digitalWrite(green,LOW);
     
  }
  else
  {
   digitalWrite(red,LOW);
      digitalWrite(green,HIGH);
  }
  sendata();
  delay(500);
}
void sendata()
{
  Serial.print('*');

  //temperature value  
  if(t <= 9){Serial.print("00");Serial.print(t);}
  else if(t <= 99){Serial.print("0");Serial.print(t);}
  else if(t <= 999){Serial.print(t);}

  //humidity value
  if(h <= 9){Serial.print("00");Serial.print(h);}
  else if(h <= 99){Serial.print("0");Serial.print(h);}
  else if(h <= 999){Serial.print(h);}

  if(gasv <= 9){Serial.print("00");Serial.print(gasv);}
      else if(gasv <= 99){Serial.print("0");Serial.print(gasv);}
      else if(gasv <= 999){Serial.print(gasv);}

       if(firev<= 9){Serial.print("00");Serial.print(firev);}
    else if(firev <= 99){Serial.print("0");Serial.print(firev);}
    else if(firev <= 999){Serial.print(firev);}
}