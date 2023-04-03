unsigned short i;

void main() {

  // Initialize USART module (8 bit, 2400 baud rate, no parity bit..)
  Usart_Init(2400);

  do {
    if (Usart_Data_Ready()) {   // If data is received
      i = Usart_Read();         // Read the received data
      Usart_Write(i);           // Send data via USART
    }
  } while (1);
}//~!