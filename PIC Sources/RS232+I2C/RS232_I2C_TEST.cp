#line 1 "D:/pic/RS232+I2C/RS232_I2C_TEST.c"
unsigned short i;

void main() {


 TRISA=0;
 Usart_Init(56000);

 do {
 PORTA.F0=0;
 if (Usart_Data_Ready()) {
 i = Usart_Read();
 Usart_Write(i);
 PORTA.F0 = 1;
 delay_ms(10);
 }
 } while (1);
}
