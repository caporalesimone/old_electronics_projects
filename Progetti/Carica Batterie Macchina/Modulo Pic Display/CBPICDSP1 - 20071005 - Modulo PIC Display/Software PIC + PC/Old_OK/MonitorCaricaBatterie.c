
/* Questo progetto consiste nello sviluppo di un modulo di monitoraggio
   della carica di un caricabatteria da Auto
   

   MCU per lo sviluppo          : PIC16F877A @ 8Mhz
   MCU installata nel prototipo : PIC16F876A @ 20Mhz

   Vengono utilizzati 2 segnali analogici per la lettura della tensione
   e della corrente di carica
   
   N.B
   
   La PORTC ha impegnati RC6 e RC7 perchè utilizzati per il collegamento
   RS232 del Bootloader.

*/


#define MAX_V1_BATTERIA 1650  //Massima tensione letta sulla batteria
                              //Per semplificare i calcoli la tensione va
                              //indicata moltiplicata per 100
#define MAX_V2_BATTERIA 1650

#define NUM_LETTURE 400       //Numero di letture prima di visualizzare il dato
#define TEMPO_LETTURA 1       //Tempo in millisecondi tra una lettura e l'altra

//Queste sono le stringe che appaiono sul display LCD. Memorizzandole come
// const char, vengono salvate in ROM e, non occupano Ram
const char txt_avvio1[] = "Monitor Batteria";
const char txt_avvio2[] = "CSTech  Set 2007";

const char txt_riga1[]  = "AUDI A6 :   .  V";
const char txt_riga2[]  = "MERCEDES:   .  V";

//Questa funzione prende una stringa dalla rom, la copia in RAM e la
// visualizza sul Diaplay LCD
void rom_str2lcd (unsigned char riga, unsigned char col ,char const *str_in_ROM)
{
  unsigned short i = 0;
  char txt_msg[16];

  do {
     txt_msg[i] = str_in_ROM[i];
  } while (str_in_ROM[i++]);

  LCD_Out(riga,col,txt_msg);
}


// Vengono settate le costanti per il funzionamento della MCU
void init_MCU (void)
{
  INTCON = 0;  // Disabilita gli interrupt

  ADCON1 = 0b11000100; // AN0 AN1 AN3 sono ingressi analogici
                       // contano gli ultimi 4 bit 0100 (pag 130 DataSheet)

  TRISA = 0b11011111; //  Setto la PORTA
  TRISB = 0x00;  //  Setto la PORTB come output
  TRISC = 0x00;  //  Setto la PORTC come output
}
   

// Inizializza il diplay LCD e visualizza la schermata principale
void start_LCD()
{
  Lcd_Init(&PORTB);  // Inizializza l'LCD sulla PORTD
  Delay_ms(5);
  Lcd_Cmd(LCD_CLEAR);  // Clear display
  Delay_ms(5);
  Lcd_Cmd(LCD_CURSOR_OFF);  // Disattiva il cursore
  Delay_ms(250);
}

// Prende in ingresso i valori dei due ADC e li visualizza sul Display

void Display_Tensione(unsigned int adcVolt1, unsigned int adcVolt2)
{
  long tensione1;
  long tensione2;
  unsigned char ch;

  tensione1 = (MAX_V1_BATTERIA * (unsigned long)adcVolt1) / 1023;
  tensione2 = (MAX_V2_BATTERIA * (unsigned long)adcVolt2) / 1023;

  //Divido i valori per poterli visualizzare

  ch = tensione1 / 1000;
  LCD_Chr(1,11,48+ch);
  ch = (tensione1 / 100) % 10;
  LCD_Chr_CP(48+ch);
  LCD_Chr_CP('.');
  ch = (tensione1 / 10) % 10;
  LCD_Chr_CP(48+ch);
  ch = tensione1 % 10;
  LCD_Chr_CP(48+ch);

  ch = tensione2 / 1000;
  LCD_Chr(2,11,48+ch);
  ch = (tensione2 / 100) % 10;
  LCD_Chr_CP(48+ch);
  LCD_Chr_CP('.');
  ch = (tensione2 / 10) % 10;
  LCD_Chr_CP(48+ch);
  ch = tensione2 % 10;
  LCD_Chr_CP(48+ch);
}


void main ()
{
  unsigned long int adc_volt1;
  unsigned long int adc_volt2;

  int i;

  init_MCU();

  PORTA.F5 = 1;
  start_LCD();

  Lcd_Cmd(Lcd_CLEAR);  // Clear display
  
  rom_str2lcd(1,1,txt_avvio1);
  rom_str2lcd(2,1,txt_avvio2);

  Delay_ms(2000);

  Lcd_Cmd(Lcd_CLEAR);  // Clear display

  rom_str2lcd(1,1,txt_riga1);
  rom_str2lcd(2,1,txt_riga2);

  //PORTC.F3 = 0;
  //PORTA.F5 = 1;


  while (1)
  {

    adc_volt1 = 0;
    adc_volt2 = 0;

    for (i=0;i<NUM_LETTURE;i++){
       adc_volt1 = adc_volt1 + ADC_read(0);  //AN0
       adc_volt2 = adc_volt2 + ADC_read(1);  //AN1
       Delay_ms(TEMPO_LETTURA);

       if (PORTA.F2 == 0) {
          PORTA.F5 = 0;
       }

       if (PORTA.F2 == 1) {
          PORTA.F5 = 1;
       }
    }

    adc_volt1 = adc_volt1 / NUM_LETTURE;
    adc_volt2 = adc_volt2 / NUM_LETTURE;

    Display_Tensione (adc_volt1, adc_volt2);
  }

}
   
   
   
   
   

