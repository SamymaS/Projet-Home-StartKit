#include <ESP32Tone.h>
#include <musicESP32_home.h>   
music Music(25);
#define btn1 16
int btn_count = 0; //Used to count the clicked button times 
boolean music_flag = 0;

void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT);
  pinMode(25, OUTPUT);
//  Music.tetris();
//  Music.birthday();
//  Music.Ode_to_Joy();
//  Music.christmas();
//  Music.super_mario();
//  Music.star_war_tone();
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
        {
          music_flag = 1;
          btn_count++;    //Automatically increments by 1 to count the number of times the button is clicked
          Serial.println(btn_count);
          if(btn_count == 4)
          {
            btn_count = 1;
          }
          switch(btn_count)
          {
            case 1: if(music_flag == 1){Music.Ode_to_Joy();music_flag=0;} break;
            case 2: if(music_flag == 1){Music.christmas();music_flag=0;} break;
            case 3: if(music_flag == 1){Music.tetris();music_flag=0;} break;
          }
          btn_state = 0;  //The button is released and exits the loop
        }
      }
    }
  }
}
