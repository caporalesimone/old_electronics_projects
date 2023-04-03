unsigned short i;

void main() {

  // Initialize USART module (8 bit, 2400 baud rate, no parity bit..)
  TRISA=0;
  Usart_Init(56000);

  do {
    PORTA.F0=0;
    if (Usart_Data_Ready()) {   // If data is received
      i = Usart_Read();         // Read the received data
      Usart_Write(i);           // Send data via USART
      PORTA.F0 = 1;
      delay_ms(10);
    }
  } while (1);
}//~!


