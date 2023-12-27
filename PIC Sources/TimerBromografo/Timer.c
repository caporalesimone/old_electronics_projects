/*

   Timer per il bromografo con PIC16F84A

   RB0-3 -> 4 Bit del numero da visualizzare sul diplay
   RB4-6 -> 3 Bit che indicano quale diplay e da visualizzare (Multiplexing)
   RB7   -> 1 Bit che abilita o disabilita un output
   
   RA0   -> Tasto 1 (Start o Stop del conteggio)
   RA1   -> Tasto 2 (Set o Store dei secondi da conteggiare)
   RA2   -> Tasto 3 (Aumenta i secondi per il conteggio)
   RA3   -> Tasto 4 (Diminuisce i secondi per il conteggio)
   
   N.B. E' stato sviluppato per un quarzo da 4Mhz

*/

//#define XTAL_FREQ 4MHZ
#define DISPLAY_VALUE PORTB

unsigned char ucNumDisplay;  // Numero del diplay attivo in un certo istante
int uiSecondi_Attuale;   // Numero di secondi trascorsi. Deve essere signed!
unsigned int uiSecondi_Fine; // Numero di secondi a cui fermare il conteggio
unsigned char ucOutEnabled;  // Abilita l'uscita se è uguale a 128

unsigned int uiContTmp;      // Contatore temporaneo per gli interrupt

// Gestion dell'interrupt
void interrupt() {
  uiContTmp++;
  TMR0 = 96;
  INTCON = 0x20;       // Set T0IE, clear T0IF
}

// Procedura per visualizzare uiSecondi_Attuale
void DisplayNum (void) {
 unsigned char ucSecondi_Unita;
 unsigned char ucSecondi_Decine;
 unsigned char ucSecondi_Minuti;
 unsigned int uiSecondi;

 // Evito di fare i conti se uiSecondi_Attuale è nullo
 if (uiSecondi_Attuale > 0)  {
    uiSecondi = uiSecondi_Attuale;

    ucSecondi_Minuti = uiSecondi / 60;
    uiSecondi =  uiSecondi % 60;
    ucSecondi_Decine = uiSecondi / 10;
    ucSecondi_Unita = uiSecondi % 10;
 }
 else
 {
    ucSecondi_Minuti = 0;
    ucSecondi_Decine = 0;
    ucSecondi_Unita = 0;
 }

 switch(ucNumDisplay)
 {
   case 0: // Display delle unità di secondi
        DISPLAY_VALUE = ucSecondi_Unita;
        DISPLAY_VALUE = DISPLAY_VALUE + 16 + ucOutEnabled;
   break;
   case 1: // Display delle decine di secondi
        DISPLAY_VALUE = ucSecondi_Decine;
        DISPLAY_VALUE = DISPLAY_VALUE + 32 + ucOutEnabled;
   break;
   case 2: // Display dei minuti
        DISPLAY_VALUE = ucSecondi_Minuti;
        DISPLAY_VALUE = DISPLAY_VALUE + 64 + ucOutEnabled;
   break;
 }
 ucNumDisplay++;
 if (ucNumDisplay >= 3) ucNumDisplay = 0;
} // END void DisplayNum (void)


void main (void) {
  char cEsciLoop;
  unsigned int i; // Variabile temporanea per i contatori
  unsigned char j,k; // Variabili temporanea per accelerare i tasti UP/DOWN
  unsigned int uiMaxInterrupt; // Numero di interrupt per fare un secondo
  

  //Delay_ms(1000);

  // Configurazione delle porte
  PORTB = 0;
  PORTA = 0;
  TRISA = 0xFF; // INPUT
  TRISB = 0x00; // OUTPUT

  // Configurazione del timer
  OPTION_REG = 0x84;   // Assign prescaler to TMR0
  uiContTmp = 0;
  TMR0 = 96;

  //Leggo dalla Flash memory il tempo settato in precedenza
  //uiSecondi_Fine = Flash_Read(0x0A30);
  //if (uiSecondi_Fine >= 585) uiSecondi_Fine = 585;
  
  uiSecondi_Fine = Eeprom_Read(1);
  Delay_ms(250);
  uiSecondi_Fine = uiSecondi_Fine + (256 * Eeprom_Read(3));
  if (uiSecondi_Fine >= 585) uiSecondi_Fine = 585;

  
  //uiSecondi_Fine = 180; // 3 Minuti di default
  uiSecondi_Attuale = uiSecondi_Fine; // Setto il contatore dei secondi trascorsi
  ucOutEnabled = 0; // Uscita disattivata (Carico spento)
  
  uiMaxInterrupt = 187;

  while (1)
  {
    DisplayNum();

    // GESTIONE DELLA PRESSIONE DEL TASTO 1 (START/STOP)
    if (PORTA.F0 == 0)
    {
      //Evito che ci siano problemi se si tiene premuto a lungo il tasto
      while (PORTA.F0 == 0) { }
      
      INTCON = 0xA0;       // Enable TMRO interrupt
      uiSecondi_Attuale = uiSecondi_Fine;
      while (uiSecondi_Attuale > 0)
        {
          ucOutEnabled = 128; // Abilita l'output (Relay)
          DisplayNum();

          if (uiContTmp >= uiMaxInterrupt)  // Era 200 per un secondo
          {
            uiSecondi_Attuale--;
            uiContTmp = 0;
            // Recupera del tempo se supera i 2 minuti in modo da correggere
            // la deriva temporale.
            if (uiSecondi_Attuale < 120) uiMaxInterrupt = 180;
          }
          // Premuto il tasto 0 come stop ma fermo solo se sono trascorsi
          // almeno 2 secondi

          if ((PORTA.F0 == 0) && (uiSecondi_Attuale < uiSecondi_Fine - 5))
          {
            //Evito che ci siano problemi se si tiene premuto a lungo il tasto
            while (PORTA.F0 == 0) { }
            break;
          }
         } // END while (uiSecondi_Attuale < uiSecondi_Fine)
      INTCON = 0x00;         // Disable TMRO interrupt
      // Risetto il contatore dei secondi trascorsi
      uiSecondi_Attuale = uiSecondi_Fine;
      ucOutEnabled = 0;
    } // END Gesione tasto 1 (START/STOP)

    // GESTIONE DELLA PRESSIONE DEL TASTO 2 (SET/STORE)
    if (PORTA.F1 == 0)
    {
      cEsciLoop = 0;
      //Evito che ci siano problemi se si tiene premuto a lungo il tasto
      while (PORTA.F1 == 0) { }

      uiSecondi_Attuale = uiSecondi_Fine;

      while (cEsciLoop == 0)
      {
        DisplayNum();
        j = 0;
        k = 1;

        // BOTTONE 3 (UP)
        while (PORTA.F2 == 0)
        {
          j = j + k;
          if (j >= 10)  k = 5;  // Anzichè di incrementare di uno incremento
          if (j >= 60)  k = 30; // di 5 e poi di 30 per fare prima.

          //Ciclo di 50ms circa di visualizzazione dei diplay
          for (i=0;i<50;i++) {
            DisplayNum();
            Delay_ms(1);
          }

          if (uiSecondi_Attuale + k  < 599)
                    uiSecondi_Attuale = uiSecondi_Attuale + k;
          else uiSecondi_Attuale = 1;

          for (i=0;i<50;i++) {
            DisplayNum();
            Delay_ms(1);
          }
        } // END while (PORTA.F2 == 0)

        // BOTTONE 4 (DOWN)
        while (PORTA.F3 == 0)
        {
          j = j + k;
          if (j >= 10)  k = 5;
          if (j >= 60)  k = 30;

          for (i=0;i<50;i++)
          {
            DisplayNum();
            Delay_ms(1);
          }

          if (uiSecondi_Attuale > 1)
                    uiSecondi_Attuale = uiSecondi_Attuale - k;
          else uiSecondi_Attuale = 599;

          for (i=0;i<50;i++)
          {
            DisplayNum();
            Delay_ms(1);
          }
        } // END while (PORTA.F3 == 0)

        // TASTO SET/STORE IN MODALITA' STORE
        if (PORTA.F1 == 0)
        {
          cEsciLoop = 1;
          //Evito che ci siano problemi se si tiene premuto a lungo il tasto
          while (PORTA.F1 == 0) { }

          uiSecondi_Fine = uiSecondi_Attuale;

          // Scrivo in Flash Memory i secondi
          //Flash_Write(0x0A30,uiSecondi_Fine);
          EEprom_Write(1, uiSecondi_Fine & 0b11111111);
          Delay_ms(250);
          EEprom_Write(3, uiSecondi_Fine / 0b11111111);
         }
      }
    } // // END Gesione tasto 2 (SET/STORE)

  } // END while(1)
} // END void main (void)



