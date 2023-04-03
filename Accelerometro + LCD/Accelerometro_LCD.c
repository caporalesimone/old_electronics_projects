#include"built_in.h"

unsigned char ch;
unsigned int t1;
char a[17], *tc;
char *tc1;
long tlong;
char i;
long somma;

void main() {
  INTCON = 0;                        // disable all interrupts
  LCD_Init(&PORTB);                  // initialize  (4-bit interface connection)
  LCD_Cmd(LCD_CURSOR_OFF);           // send command to LCD (cursor off)
  LCD_Cmd(LCD_CLEAR);                // send command  to LCD (clear LCD)

  tc = "CSTech 02/12/06";           // assign text to string a
  LCD_Out(1,1,tc);                   // print string a on LCD, 1st row, 1st column
  tc = "";                // assign text to string a
  LCD_Out(2,1,tc);                   // print string a on LCD, 2nd row, 1st column

  OPTION_REG  = 0x80;
  ADCON1     = 0x80;                 // configure VDD as Vref, and analog channels
  TRISA      = 0xFF;                 // designate porta as input
  TRISC  = 0;
  Delay_ms(2000);
  LCD_Cmd(LCD_CLEAR);
  tc  = "Volt X:";                  // assign text to string a
  tc1 = "Volt Y:";
  while (1) {
  
    somma=0;
    for (i=0;i<50;i++)
    {
      somma = somma + ADC_read(0);
      Delay_ms(5);
    }
    
    t1 = somma / 60;

    //t1  = ADC_read(0);                // get ADC value from 2nd channel
    LCD_Out(2,1,tc);                 // print string a on LCD, 2nd row, 1st column

    tlong  = t1 * 5000;               // use (int) multiplication instead of (long)
    asm {                            //   and fill the upper two bytes manually
      MOVF STACK_2,W
      MOVWF _tlong+2
      MOVF STACK_3,W
      MOVWF _tlong+3
    }
    t1= tlong >> 10;

    ch     = t1 / 1000;               // prepare value for diplay
    LCD_Chr(2,9,48+ch);              // write ASCII at 2nd row, 9th column
    LCD_Chr_CP('.');

    ch    = (t1 / 100) % 10;
    LCD_Chr_CP(48+ch);

    ch    = (t1 / 10) % 10;
    LCD_Chr_CP(48+ch);

    ch    = t1 % 10;
    LCD_Chr_CP(48+ch);
    LCD_Chr_CP('V');

    //t1  = ADC_read(1);                // get ADC value from 2nd channel

    somma=0;
    for (i=0;i<50;i++)
    {
      somma = somma + ADC_read(1);
      Delay_ms(5);
    }
    t1 = somma / 60;

    LCD_Out(1,1,tc1);                 // print string a on LCD, 2nd row, 1st column

    tlong  = t1 * 5000;               // use (int) multiplication instead of (long)
    asm {                            //   and fill the upper two bytes manually
      MOVF STACK_2,W
      MOVWF _tlong+2
      MOVF STACK_3,W
      MOVWF _tlong+3
    }
    t1= tlong >> 10;

    ch     = t1 / 1000;               // prepare value for diplay
    LCD_Chr(1,9,48+ch);              // write ASCII at 2nd row, 9th column
    LCD_Chr_CP('.');

    ch    = (t1 / 100) % 10;
    LCD_Chr_CP(48+ch);

    ch    = (t1 / 10) % 10;
    LCD_Chr_CP(48+ch);

    ch    = t1 % 10;
    LCD_Chr_CP(48+ch);
    LCD_Chr_CP('V');

    Delay_ms(400);
  }
}//~!

