/*
 * Project name:
     PWM1_Test_01 (PWM1 library Demonstration)
 * Copyright:
     (c) Mikroelektronika, 2005.
 * Description:
     This is a simple demonstration of PWM1 library, which is being used for
     control of the PIC's CCP module. The module is initialized and started,
     after which the PWM1 Dyty Ratio can be adjusted by means of two buttons
     connected to pins RA0 and RA1. The changes can be monitored on the CCP
     output pin (RC2).
 * Test configuration:
     MCU:             PIC16F877A
     Dev.Board:       EasyPIC4
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:     -
     SW:              mikroC v6.0
 * NOTES:
     None.
*/

unsigned short j, oj;

void InitMain() {
  PORTB = 0;                     // set PORTB to 0
  TRISB = 0;                     // designate portb pins as output

  ADCON1 = 6;                    // all ADC pins to digital I/O
  PORTA = 255;
  TRISA = 255;                   // PORTA is input

  PORTC = 0x0;                   // set PORTC to $FF
  TRISC = 0;                     // designate PORTC pins as output
  PWM1_Init(200000);                // initialize PWM1 module
  PWM2_Init(200000);                // initialize PWM1 module                                                           PWM1_Init(5000);                // initialize PWM1 module
}//~

void main() {
  initMain();

  j     = 127;                   // initial value for j
  oj    = 0;                     // oj will keep the 'old j' value
  PWM1_Start();                   // start PWM1
  PWM2_Start();

  while (1) {                    // endless loop
    if (Button(&PORTA, 0,1,1))   // button on RA0 pressed
      j=j+10 ;                      //    increment j
    if (Button(&PORTA, 1,1,1))   // button on RA1 pressed
      j=j-10 ;                      //    decrement j

    if (oj != j) {               // if change in duty cycle requested
      PWM1_Change_Duty(j);        //    set new duty ratio,
      PWM2_Change_Duty(j);        //    set new duty ratio,
      oj = j;                    //    memorize it
      PORTB = oj;                //    and display on PORTB
    }
    Delay_ms(200);               // slow down change pace a little
  }
}//~!

