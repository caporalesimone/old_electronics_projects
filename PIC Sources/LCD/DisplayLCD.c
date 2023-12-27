
char *text0 = "ABCDEFGHILMN";
char *text1 = "OPQRSTUVWXYZ";


void main() {
  LCD_Init(&PORTB);         // Initialize LCD connected to PORTB
  LCD_Cmd(LCD_CLEAR);       // Clear display
  LCD_Cmd(LCD_CURSOR_OFF);  // Turn cursor off

  LCD_Out(1,1, text0);
  LCD_Out(2,1, text1);

  while(1)
  {

  }
  
  
  
}//~!

