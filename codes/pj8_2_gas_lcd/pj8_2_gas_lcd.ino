#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(0x27,16,2);
#define gasPin 23
#define buzPin 25
boolean i = 1;
boolean j = 1;

void setup(){
  Serial.begin(9600);
  mylcd.init();
  mylcd.backlight();
  pinMode(buzPin, OUTPUT);
  pinMode(gasPin, INPUT);
  mylcd.setCursor(0, 0);
  mylcd.print("safety");
}

void loop(){
  boolean gasVal = digitalRead(gasPin);  //Reads the value detected by the gas sensor
  Serial.println(gasVal);
  if(gasVal == 0)  //If the hazardous gas is detected，LCD displays dangerous，the buzzer makes an alarm
  {
    while(i == 1)
    {
      mylcd.clear();
      mylcd.setCursor(0, 0);
      mylcd.print("dangerous");
      i = 0;
      j = 1;
    }
    digitalWrite(buzPin,HIGH);
    delay(1);
    digitalWrite(buzPin,LOW);
    delay(1);
  }
  else{
    digitalWrite(buzPin,LOW);
    while(j == 1)
    {
      mylcd.clear();
      mylcd.setCursor(0, 0);
      mylcd.print("safety");
      i = 1;
      j = 0;
    }
  }
}
