#include <analogWrite.h>
#define fanPin1 19
#define fanPin2 18
#define btn1 16
int btn_count = 0; //Used to count the clicked button times 
#define btn2 27
int btn_count2 = 0;
int speed_val = 130; //Define the speed variables

void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
}

void loop() {
  boolean btn1_val = digitalRead(btn1);
  if(btn1_val == 0) //If the button is pressed
  {
    delay(10);  //Delay 10ms to eliminate button jitter
    if(btn1_val == 0) //Make sure the button is pressed again  
    {
      boolean btn_state = 1;
      while(btn_state == 1) //Loop indefinitely until the button is released
      {
        boolean btn_val = digitalRead(btn1);
        if(btn_val == 1)  //If the button is released
          btn_count++;    //Automatically increments by 1 to count the clicked button times 
          Serial.println(btn_count);
          btn_state = 0;  //The button is released and exits the loop
        }
      }
    }
    boolean value = btn_count % 2; //Take the remainder of the value, you will get 0 or 1
    while(value == 1)
    {
      //Serial.println("on");
      digitalWrite(fanPin1, LOW); //pwm = 0
      analogWrite(fanPin2, speed_val);
      
      boolean btn2_val = digitalRead(btn2);
      if(btn2_val == 0)
      {
        delay(10);
        if(btn2_val == 0)
        {
          boolean btn_state2 = 1;
          while(btn_state2 == 1)
          {
            boolean btn2_val = digitalRead(btn2);
            if(btn2_val == 1)
            {
              btn_count2++;
              if(btn_count2 > 3)
              {
                btn_count2 = 1;
              }
              switch(btn_count2)
              {
                case 1: speed_val = 130; Serial.println(speed_val);break;  //Adjust the speed
                case 2: speed_val = 180; Serial.println(speed_val);break;
                case 3: speed_val = 230; Serial.println(speed_val);break;
              }
              btn_state2 = 0;
            }
          }
        }
      }
      boolean btn1_val = digitalRead(btn1);
      if(btn1_val == 0) //If the button is pressed
      {
        digitalWrite(fanPin1, LOW); //pwm = 0
        analogWrite(fanPin2, 0);
        value = 0;  //Exit the loop 
      }
      
    }
  }
}                                                                                                                                                       
