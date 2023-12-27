#line 1 "D:/pic/RS232/RS232.c"
unsigned short i;

void main() {


 Usart_Init(2400);

 do {
 if (Usart_Data_Ready()) {
 i = Usart_Read();
 Usart_Write(i);
 }
 } while (1);
}
