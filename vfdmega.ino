/*
  SINEWAVE Generator for 3-Phase Motor
  Kash Patel 
  DATE:18/05/2021
  Tested OK
*/
int led1 = 3;  
int led2 = 9;    
int led3 = 10;  
int led4 = 11;   
int led5 = 5;  
int led6 = 6;   
unsigned long counter=0;     // 32 bit counter
int brightness = 0;    // set the LED brightness
int brightness2 =-170;    // set the LED brightness
int brightness3 = +170;    // set the LED brightness
int fadeAmount = 5;    // 5 points to fade the LED   
int fadeAmount2 = -5;    // 5 points to fade the LED 
int fadeAmount3 = +5;    // 5 points to fade the LED 

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
}

void loop() {
   if (brightness>=0)
  {
   analogWrite(led1, brightness);
   analogWrite(led2, 0);
  }
  else
  {  
   analogWrite(led1, 0);
   analogWrite(led2,-brightness);  
  
  }
   brightness = brightness + fadeAmount;
  
  if (brightness >= 255 || brightness <= -255)
  {
        fadeAmount = -fadeAmount;
  }
//--------------------------------------------------------------  
  if (brightness2>=0)
  {
   analogWrite(led3, brightness2);
   analogWrite(led4, 0);
  }
  else
  {  
   analogWrite(led3, 0);
   analogWrite(led4,-brightness2);  
  
  }
   brightness2 = brightness2 + fadeAmount2;
  
  if (brightness2 >= 255 || brightness2 <= -255)
  {
      fadeAmount2 = -fadeAmount2;
  }
//--------------------------------------------------------------  

  if (brightness3>=0)
  {
   analogWrite(led5, brightness3);
   analogWrite(led6, 0);
  }
  else
  {  
   analogWrite(led5, 0);
   analogWrite(led6,-brightness3);  
  
  }
   brightness3 = brightness3 + fadeAmount3;
  
  if (brightness3 >= 255 || brightness3 <= -255)
  {
      fadeAmount3 = -fadeAmount3;
  }
  
  delay(1);

} 
