#line 1 "D:/PIC/Hitachi/DisplayLCD.c"

char *text0 = "ABCDEFGHILMN";
char *text1 = "OPQRSTUVWXYZ";


void main() {
 LCD_Init(&PORTB);
 LCD_Cmd(LCD_CLEAR);
 LCD_Cmd(LCD_CURSOR_OFF);

 LCD_Out(1,1, text0);
 LCD_Out(2,1, text1);

 while(1)
 {

 }



}
