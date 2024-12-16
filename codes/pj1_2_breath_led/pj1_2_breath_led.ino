#include <analogWrite.h>  //Import PWM output library files
#define led_y 12    //Define LED pins  

void setup(){
  pinMode(led_y, OUTPUT);  //Set pin to output mode
}

void loop(){
  for(int i=0; i<255; i++)  //The for loop statement increments the value of variable i until it exits the loop at 255  
  {
    analogWrite(led_y, i);  //PWM output, control LED brightness
    delay(3);
  }
  for(int i=255; i>0; i--)  //The for loop statement continues to decrease the value of variable i until it exits the loop at 0
    analogWrite(led_y, i);
    delay(3);
  }
}
