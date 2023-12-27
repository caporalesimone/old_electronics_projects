#include"built_in.h"

unsigned char ch;
unsigned int t;
char a[17], *tc;
long tlong;

void main() {
  INTCON = 0;                        // disable all interrupts
  LCD_Init(&PORTB);                  // initialize  (4-bit interface connection)
  LCD_Cmd(LCD_CURSOR_OFF);           // send command to LCD (cursor off)
  LCD_Cmd(LCD_CLEAR);                // send command  to LCD (clear LCD)

  tc = "mikroElektronika";           // assign text to string a
  LCD_Out(1,1,tc);                   // print string a on LCD, 1st row, 1st column
  tc = "LCD example";                // assign text to string a
  LCD_Out(2,1,tc);                   // print string a on LCD, 2nd row, 1st column

  OPTION_REG  = 0x80;
  ADCON1     = 0x82;                 // configure VDD as Vref, and analog channels
  TRISA      = 0xFF;                 // designate porta as input
  TRISC  = 0;
  TRISD  = 0;
  Delay_ms(2000);
  tc  = "voltage:";                  // assign text to string a
  while (1) {
    t  = ADC_read(1);                // get ADC value from 2nd channel
    LCD_Out(2,1,tc);                 // print string a on LCD, 2nd row, 1st column

    tlong  = t * 5000;               // use (int) multiplication instead of (long)
    asm {                            //   and fill the upper two bytes manually
      MOVF STACK_2,W
      MOVWF _tlong+2
      MOVF STACK_3,W
      MOVWF _tlong+3
    }
    t = tlong >> 10;

    ch     = t / 1000;               // prepare value for diplay
    LCD_Chr(2,9,48+ch);              // write ASCII at 2nd row, 9th column
    LCD_Chr_CP('.');

    ch    = (t / 100) % 10;
    LCD_Chr_CP(48+ch);

    ch    = (t / 10) % 10;
    LCD_Chr_CP(48+ch);

    ch    = t % 10;
    LCD_Chr_CP(48+ch);
    LCD_Chr_CP('V');

    Delay_ms(1);
  }
}//~!

