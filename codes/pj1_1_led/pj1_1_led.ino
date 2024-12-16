#include <xht11.h>

/*#define led_y 12  //Define the yellow led pin to 12

void setup() {             //The code inside the setup function runs only once
  pinMode(led_y, OUTPUT);  //Set pin to output mode
}

void loop() {                 //The code inside the loop function will always run in a loop
  digitalWrite(led_y, HIGH);  //Light up the LED
  delay(200);                 //Delay statement, in ms
  digitalWrite(led_y, LOW);   //Close the LED
  delay(200);
}


*/

#include <analogWrite.h>  //Import PWM output library files
#define led_y 12          //Define LED pins


  void setup() {
   pinMode(led_y, OUTPUT);  //Set pin to output mode
}


void loop() {
  for (int i = 0; i < 255; i++)  //The for loop statement increments the value of variable i until it exits the loop at 255
  {
    analogWrite(led_y, i);  //PWM output, control LED brightness
    delay(3);
  }
  for (int i = 255; i > 0; i--) //The for loop statement continues to decrease the value of variable i until it exits the loop at 0 
  {  
    analogWrite(led_y, i);
    delay(3);
  }
}


