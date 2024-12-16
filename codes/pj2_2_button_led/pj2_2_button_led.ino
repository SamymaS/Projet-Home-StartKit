#define btn1 16
#define led_y 12
int btn_count = 0; //Used to count the clicked button times 

void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT);
  pinMode(led_y, OUTPUT);
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
          btn_count++;    //Automatically increments by 1, account the  clicked button times
          Serial.println(btn_count);
          btn_state = 0;  //The button is released and exits the loop
        }
      }
    }
    boolean value = btn_count % 2; //Take the remainder of the value, you will get 0 or 1
    if(value == 1)
    {
      digitalWrite(led_y, HIGH);
    }
    else{
      digitalWrite(led_y, LOW);
    }
  }
}                                                                                                                                                            
