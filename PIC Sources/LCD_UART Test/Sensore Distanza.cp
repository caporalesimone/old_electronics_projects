#line 1 "C:/Programmazione/MikroC/Sensore distanza sonar/Sensore Distanza.c"



sbit LCD_RS at LATD2_bit;
sbit LCD_EN at LATD3_bit;
sbit LCD_D4 at LATD4_bit;
sbit LCD_D5 at LATD5_bit;
sbit LCD_D6 at LATD6_bit;
sbit LCD_D7 at LATD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;


const char txt_start1[] = "Caporale Simone";
const char txt_start2[] = "Aprile 2013";






void LCD_Out_const(char x, char y, const char *txt){
 char loc_text[ 20 ];
 char * dst;

 dst = loc_text;
 while (*dst++ = *txt++);

 LCD_Out(x, y, loc_text);
}

void interrupt(){
#line 54 "C:/Programmazione/MikroC/Sensore distanza sonar/Sensore Distanza.c"
}




void hardware_default_setup (void) {

 INTCON = 0x00;
 PIE1 = 0x00;
 PIE2 = 0x00;
 PIR1 = 0x00;
 PIR2 = 0x00;
 IPR1 = 0x00;
 IPR2 = 0x00;
 CMCON |= 7;

 ADCON0 = 0x00;
 ADCON1 = 0b00001111;

 TRISA = 0xFF;
 TRISB = 0xFF;
 TRISC = 0xFF;
 TRISD = 0xFF;
 TRISE = 0xFF;
}


void hardware_specific_setup (void) {

 TRISD = 0b00000011;








}


void main(void) {

 char uart_rd = 0;
 char x,y;
 char out_str[20];

 hardware_default_setup();
 hardware_specific_setup();
 Delay_ms(10);
 Lcd_Init();

 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 LCD_Out_const(1,1,txt_start1);
 LCD_Out_const(2,1,txt_start2);

 Delay_ms(3000);

 Lcd_Cmd(_LCD_CLEAR);

 UART1_Init(115200);
 Delay_ms(100);

 UART1_Write_Text("Start");
 UART1_Write(10);
 UART1_Write(13);

 x = 1;
 y = 1;
 while (1) {
 if (UART1_Data_Ready()) {
 uart_rd = UART1_Read();
 Lcd_Chr(y,x,uart_rd);

 sprinti(out_str,"X=%d",(int)x);
 UART1_Write_Text(out_str);
 sprinti(out_str," - Y=%d\r\n",(int)y);
 UART1_Write_Text(out_str);

 x++;

 if (x == 17) {
 x = 1;
 y++;
 if (y == 3) {
 x = 1;
 y = 1;
 Lcd_Cmd(_LCD_CLEAR);
 }
 }
 }
 }


}
