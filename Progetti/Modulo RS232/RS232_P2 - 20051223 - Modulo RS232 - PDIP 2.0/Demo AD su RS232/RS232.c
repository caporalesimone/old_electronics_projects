/*
 * Project name:
     ADC_USART (Transferring ADC data on Serial port)
 * Copyright:
     (c) Mikroelektronika, 2005.
 * Description:
     The code performs AD conversion and sends results (the upper 8 bits) via
     USART.
 * Test configuration:
     MCU:             P16F877A
     Dev.Board:       EasyPIC2
     Oscillator:      HS, 08.0000 MHz
     Ext. Modules:    -
     SW:              mikroC v2.00
 * NOTES:
     None.
*/

unsigned short temp_res;

void main() {
  USART_Init(57600);  // Initalize USART (9600 baud rate, 1 stop bit, ...

  // Select Vref and analog inputs, in order to use ADC_Read
  ADCON1 = 0;        // All porta pins as analog, VDD as Vref
  TRISA  = 0xFF;     // PORTA is input

  do {

    // Read ADC results and send the upper byte via USART
    temp_res = ADC_Read(2) >> 2;
    USART_Write(temp_res);
  } while (1);
}

