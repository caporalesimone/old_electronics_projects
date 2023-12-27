
// Configurazione del display LCD

sbit LCD_RS at LATD2_bit;  // for writing to output pin always use latch (PIC18 family)
sbit LCD_EN at LATD3_bit;  // for writing to output pin always use latch (PIC18 family)
sbit LCD_D4 at LATD4_bit;  // for writing to output pin always use latch (PIC18 family)
sbit LCD_D5 at LATD5_bit;  // for writing to output pin always use latch (PIC18 family)
sbit LCD_D6 at LATD6_bit;  // for writing to output pin always use latch (PIC18 family)
sbit LCD_D7 at LATD7_bit;  // for writing to output pin always use latch (PIC18 family)

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

#define __MAX_STRING_LENGTH 20
const char txt_start1[] = "Caporale Simone";
const char txt_start2[] = "Aprile 2013";

//char i;                              // Loop variable
//char pressedButton;
//bit flag;

// Funzione che ottimizza l'utilizzo della ram nella stampa di stringhe
void LCD_Out_const(char x, char y, const char *txt){
  char loc_text[__MAX_STRING_LENGTH];
  char * dst;

  dst = loc_text;
  while (*dst++ = *txt++);

  LCD_Out(x, y, loc_text);
}

void interrupt(){              // Interrupt rutine
// if(RBIF_bit == 1 ) {         // Checks for Receive Interrupt Flag bit
//    flag  = 1;                 // Set local interrupt flag
//    RBIF_bit = 0;              // Clear Interrupt Flag
//    if (PORTB.F7 == 1){        // Checks if the RB7 is pressed
//       pressedButton = 7;
//    }
//    if (PORTB.F6 == 1){        // Checks if the RB6 is pressed
//       pressedButton = 6;
//    }
//    if (PORTB.F5 == 1){        // Checks if the RB5 is pressed
//       pressedButton = 5;
//    }
//    if (PORTB.F4 == 1){        // Checks if the RB4 is pressed
//       pressedButton = 4;
//    }
//  }
}


// Inizializzazione di default di tutto l'hardware.
// Tutti i pin in digitale e in input
void hardware_default_setup (void) {

  INTCON = 0x00; // Disabilita tutti gli interrupt. Verranno settati dopo
  PIE1 = 0x00;   // Peripheral interrupt enable bits
  PIE2 = 0x00;   // Peripheral interrupt enable bits
  PIR1 = 0x00;   // Peripheral interrupt flag bits
  PIR2 = 0x00;   // Peripheral interrupt flag bits
  IPR1 = 0x00;   // Interrupt priority LOW
  IPR2 = 0x00;   // Interrupt priority LOW
  CMCON  |= 7;   // Disable comparators

  ADCON0 = 0x00;       // ADC disabilitato
  ADCON1 = 0b00001111; // Configura tuttu i pin AN come digitali

  TRISA = 0xFF; // Setta la PORTA tutta in input
  TRISB = 0xFF; // Setta la PORTB tutta in input
  TRISC = 0xFF; // Setta la PORTC tutta in input
  TRISD = 0xFF; // Setta la PORTD tutta in input
  TRISE = 0xFF; // Setta la PORTE tutta in input
}

// Inizializza in maniera specifica tutto quello che serve per questa applicazione
void hardware_specific_setup (void) {

  TRISD = 0b00000011; // Setta in output pin della porta D utilizzati dal Display

//  GIE_bit   = 1;         // General Interrupt Enable - Abilita tutti gli interrupt
//  RBIE_bit  = 1;         // RB Port Change Interrupt Enable bit
//  RBIF_bit  = 0;         // RB Port Change Interrupt Flag bit

//  INTCON.GIE   = 1;         // General Interrupt Enable - Abilita tutti gli interrupt
//  INTCON.RBIE  = 1;         // RB Port Change Interrupt Enable bit
//  INTCON.RBIF  = 0;         // RB Port Change Interrupt Flag bit
}


void main(void) {

  char uart_rd = 0;
  char x,y;
  char out_str[20];

  hardware_default_setup();    // Inizializzazione di default della MCU
  hardware_specific_setup();   // Inizializzazione specifica per questa applicazione
  Delay_ms(10);
  Lcd_Init();                  // Inizializza il display LCD

  Lcd_Cmd(_LCD_CLEAR);         // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);    // Cursor off
  LCD_Out_const(1,1,txt_start1);
  LCD_Out_const(2,1,txt_start2);

  Delay_ms(3000);

  Lcd_Cmd(_LCD_CLEAR);         // Clear display

  UART1_Init(115200);            // Initialize UART module at 9600 bps
  Delay_ms(100);               // Wait for UART module to stabilize

  UART1_Write_Text("Start");
  UART1_Write(10);
  UART1_Write(13);

  x = 1;
  y = 1;
  while (1) {                     // Endless loop
    if (UART1_Data_Ready()) {     // If data is received,
      uart_rd = UART1_Read();     // read the received data
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
            Lcd_Cmd(_LCD_CLEAR);         // Clear display
         }
      }
    }
  }


}