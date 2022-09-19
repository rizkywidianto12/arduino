#include "Arduino.h"
// Arduino sensored BLDC (brushless DC) motor control code
 
byte motor_speed,  bldc_hall, pwm_pin = 2;
// int fase[] {0,6,4,5,2,1,3};
int fase[] {
  0,                      // 000
  1,                      // 001
  5,                      // 101
  6,                      // 110
  3,                      // 011
  2,                      // 010
  4                       // 100
  };
void bldc_move(){                    // BLDC motor move function according to hall effect sensors status
//  Serial.println(fase[ bldc_hall]);
  // /*
  switch(fase[ bldc_hall]){
      //B 7 6 5 4 3 2
      //B W W V V U U
      //B - + - + - +

      //Phase1 A-B
        case 1:
        PORTD = B00110100;  //  Pin 7 and 4 to HIGH # W- V+ U
        break;
    
        //Phase2 C-B
        case 2:
        PORTD = B00011100;  //  Pin 3 and 4 to HIGH # W V+ U-
        break;
    
        //Phase3 C-A
        case 3:
        PORTD = B01001100;  //  Pin 3 and 6 to HIGH # W U- W+
        break;
     
        //Phase4 B-A
        case 4:
        PORTD = B11000100;  //  Pin 5 and 6 to HIGH # W+ V- U
        break;
    
        //Phase5 B-C
        case 5:
        PORTD = B11010000;  //  Pin 5 and 2 to HIGH # W V U
        break;
    
        //Phase6 A-C
        case 6:
        PORTD = B01110000;  //  Pin 7 and 2 to HIGH # W V U
        break;
  }
// */
}

void setup() {
  DDRD  |= 0xFC;                     // Configure pins 2, 3, 4, 5, 6 and 7 as outputs
  PCICR  = 1;                        // Enable pin change interrupt for pins 8 to 13
  PCMSK0 = 7;                        // Enable pin change interrupt for pins 8, 9 and 10
  // Timer2 configuration
  TCCR2A = 0;
  TCCR2B = 2;                        // Timer2 prescaler = 1/8 (Timer2 clock = 2MHz)
  TCNT2  = 0;                        // Timer2 preload value = 0
  // ADC module configuration
  ADMUX  = 0x60;                     // Configure ADC module and select channel 0
  ADCSRA = 0x84;                     // Enable ADC module with 16 division factor (ADC clock = 1MHz)
  // BLDC motor first move
   bldc_hall = PINB & 7;              // Read hall effect sensors status (PINB: read from PORTB which is arduino pins 8..13)
  bldc_move();                       // Move the BLDC motor (first move)
  Serial.begin(9600);
}

ISR (PCINT0_vect){
   bldc_hall = PINB & 7;              // Read and save hall effect sensors status (PINB: read from PORTB which is arduino pins 8..13)
  bldc_move();                       // Move the BLDC motor
}

void loop() {

}
