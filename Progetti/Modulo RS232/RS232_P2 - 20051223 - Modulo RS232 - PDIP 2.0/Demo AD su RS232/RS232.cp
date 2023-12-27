#line 1 "D:/pic/RS232/RS232.c"
#line 19 "D:/pic/RS232/RS232.c"
unsigned short temp_res;

void main() {
 USART_Init(57600);


 ADCON1 = 0;
 TRISA = 0xFF;

 do {


 temp_res = ADC_Read(2) >> 2;
 USART_Write(temp_res);
 } while (1);
}
