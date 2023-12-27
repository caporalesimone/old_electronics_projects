#line 1 "D:/PIC/Accelerometro + LCD/Accelerometro_LCD.c"
#line 1 "c:/mikroc/include/built_in.h"
#line 3 "D:/PIC/Accelerometro + LCD/Accelerometro_LCD.c"
unsigned char ch;
unsigned int t1;
char a[17], *tc;
char *tc1;
long tlong;
char i;
long somma;

void main() {
 INTCON = 0;
 LCD_Init(&PORTB);
 LCD_Cmd(LCD_CURSOR_OFF);
 LCD_Cmd(LCD_CLEAR);

 tc = "CSTech 02/12/06";
 LCD_Out(1,1,tc);
 tc = "";
 LCD_Out(2,1,tc);

 OPTION_REG = 0x80;
 ADCON1 = 0x80;
 TRISA = 0xFF;
 TRISC = 0;
 Delay_ms(2000);
 LCD_Cmd(LCD_CLEAR);
 tc = "Volt X:";
 tc1 = "Volt Y:";
 while (1) {

 somma=0;
 for (i=0;i<50;i++)
 {
 somma = somma + ADC_read(0);
 Delay_ms(5);
 }

 t1 = somma / 60;


 LCD_Out(2,1,tc);

 tlong = t1 * 5000;
 asm {
 MOVF STACK_2,W
 MOVWF _tlong+2
 MOVF STACK_3,W
 MOVWF _tlong+3
 }
 t1= tlong >> 10;

 ch = t1 / 1000;
 LCD_Chr(2,9,48+ch);
 LCD_Chr_CP('.');

 ch = (t1 / 100) % 10;
 LCD_Chr_CP(48+ch);

 ch = (t1 / 10) % 10;
 LCD_Chr_CP(48+ch);

 ch = t1 % 10;
 LCD_Chr_CP(48+ch);
 LCD_Chr_CP('V');



 somma=0;
 for (i=0;i<50;i++)
 {
 somma = somma + ADC_read(1);
 Delay_ms(5);
 }
 t1 = somma / 60;

 LCD_Out(1,1,tc1);

 tlong = t1 * 5000;
 asm {
 MOVF STACK_2,W
 MOVWF _tlong+2
 MOVF STACK_3,W
 MOVWF _tlong+3
 }
 t1= tlong >> 10;

 ch = t1 / 1000;
 LCD_Chr(1,9,48+ch);
 LCD_Chr_CP('.');

 ch = (t1 / 100) % 10;
 LCD_Chr_CP(48+ch);

 ch = (t1 / 10) % 10;
 LCD_Chr_CP(48+ch);

 ch = t1 % 10;
 LCD_Chr_CP(48+ch);
 LCD_Chr_CP('V');

 Delay_ms(400);
 }
}
