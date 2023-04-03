/* Timer con PIC16F84A rev. 2.0a 20070911

   RB0-3 -> 4 Bit del numero da visualizzare sul diplay
   RB4-6 -> 3 Bit che indicano quale diplay visualizzare (Multiplexing)
   RB7   -> 1 Bit per la gestione di un generico Output

   RA0   -> Tasto 1 (Start o Stop del conteggio)
   RA1   -> Tasto 2 (Set o Store dei secondi da conteggiare)
   RA2   -> Tasto 3 (Aumenta i secondi per il conteggio)
   RA3   -> Tasto 4 (Diminuisce i secondi per il conteggio)

*/


#define DISPLAY_VALUE PORTB
#define DEFAULT_TIME_INTERRUPT 195 // In origine era 200 per un secondo

unsigned char ucNumDisplay;  // Numero del diplay attivo in un certo istante
int uiSecondi_Attuale;       // Numero di secondi trascorsi.Deve essere signed
unsigned int uiSecondi_Fine; // Numero di secondi a cui fermare il conteggio
unsigned char ucOutEnabled;  // Gestisce l'abilitazione dell'output

unsigned int uiContTmp;      // Contatore temporaneo per gli interrupt

// Gestione dell'interrupt
void interrupt ()
{
     uiContTmp++;
     TMR0 = 96;
     INTCON = 0x20;       // Set T0IE, clear T0IF
}

// Inizializzazione della MCU
void InitMCU (void) {
     // Configurazione delle porte
     PORTB = 0;
     PORTA = 0;
     TRISA = 0xFF; // INPUT
     TRISB = 0x00; // OUTPUT

     // Configurazione del timer
     OPTION_REG = 0x84;   // Assign prescaler to TMR0
     uiContTmp = 0;
     TMR0 = 96;
}

// Gestione dell'output
void Enable_Output (char OutEnabled){
     if (OutEnabled == 1)
        ucOutEnabled = 128;
     else
        ucOutEnabled = 0;
}

// Abilita il Timer
void Abilita_Timer (char TimerEnabled) {
     if (TimerEnabled == 1)
          INTCON = 0xA0; // Enable TMRO interrupt
     else
          INTCON = 0x00; // Disable TMRO interrupt
}
// Funzione per visualizzare uiSecondi_Attuale
void DisplayNum (void)
{
     unsigned char ucSecondi_Unita;
     unsigned char ucSecondi_Decine;
     unsigned char ucSecondi_Minuti;
     unsigned int uiSecondi;

     // Evito di fare i conti se uiSecondi_Attuale è nullo
     if (uiSecondi_Attuale > 0) {
        uiSecondi = uiSecondi_Attuale;
        ucSecondi_Minuti = uiSecondi / 60;
        uiSecondi =  uiSecondi % 60;
        ucSecondi_Decine = uiSecondi / 10;
        ucSecondi_Unita = uiSecondi % 10;
     } else {
        ucSecondi_Minuti = 0;
        ucSecondi_Decine = 0;
        ucSecondi_Unita = 0;
     }

     switch(ucNumDisplay) {
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

int Carica_Sec(){
    int sec_letti;

    sec_letti = Eeprom_Read(1);
    Delay_ms(250);
    sec_letti = sec_letti + (256 * Eeprom_Read(3));
    return sec_letti;
}

void Salva_Sec(int Secondi){
     // Scrivo in Flash Memory i secondi
     //Flash_Write(0x0A30,uiSecondi_Fine);
     EEprom_Write(1, Secondi & 0b11111111);
     Delay_ms(250);
     EEprom_Write(3, Secondi / 0b11111111);
}

void main (void)
{
     unsigned int uiMaxInterrupt; // Numero di interrupt per fare un secondo
     unsigned int i;  // Variabile temporanea per i contatori
     signed int incr; // Variabile per la gestione dei tasti UP e DOWN
     unsigned int cnt_incr; // Conta di quanti secondi incremento/decremento
     
     InitMCU();
     uiMaxInterrupt = DEFAULT_TIME_INTERRUPT;

     uiSecondi_Fine = Carica_Sec(); // Carico dalla EEPROM i secondi salvati
     if (uiSecondi_Fine >= 585) uiSecondi_Fine = 30;

     uiSecondi_Attuale = uiSecondi_Fine; // Setto il contatore dei secondi trascorsi

     Enable_Output(0);
     Abilita_Timer(1);
     

     while (1) {
        DisplayNum();
        
        if (PORTA.F0 == 1) { //Pressione del tasto START/STOP
           while (PORTA.F0 == 1) { DisplayNum(); } // Antirimbalzo

           uiSecondi_Attuale = uiSecondi_Fine;
           Enable_Output(1);
           Abilita_Timer(1);

           while (uiSecondi_Attuale > 0) {
              DisplayNum();
              if (uiContTmp >= uiMaxInterrupt) {
                 uiSecondi_Attuale--;
                 uiContTmp = 0;  // Resetto il contatore di interrupt
                 // Recupera del tempo se supera i 2 minuti
                 //if (uiSecondi_Attuale < 120) uiMaxInterrupt = 180;
              }
              // Se si ripreme START/STOP dopo 3 secondi ferma il timer
              if ((PORTA.F0 == 1) && (uiSecondi_Attuale < uiSecondi_Fine - 3)){
                 while (PORTA.F0 == 1) { DisplayNum(); } // Antirimbalzo
                 break;
              }
           }
           Enable_Output(0);
           Abilita_Timer(0);
           uiSecondi_Attuale = uiSecondi_Fine;
           Delay_ms(100);
        } // Fine tasto START/STOP

        if (PORTA.F1 == 1) { // Pressione del tasto SET/STORE
           while (PORTA.F1 == 1) { DisplayNum(); } // Antirimbalzo
        
           uiSecondi_Attuale = uiSecondi_Fine;
        
           while (1) { // Ciclo che termina quando si ripreme SET/STORE

             DisplayNum();
             Delay_ms(10);

             cnt_incr = 0;
             // Pressione dei tasti UP o DOWN
             while ((PORTA.F2 == 1) || (PORTA.F3 == 1)) {
             
               DisplayNum();
             
               incr = 0;
               if (PORTA.F2 == 1) incr = 1;   // Se premo UP incremento di + 1
               if (PORTA.F3 == 1) incr = -1;  // Se premo DOWN incremento di -1

               cnt_incr++; // Tengo conto di quanto incremento

               if ((uiSecondi_Attuale < 599) && (uiSecondi_Attuale >= 1))
                    uiSecondi_Attuale = uiSecondi_Attuale + incr;
               else
                   uiSecondi_Attuale = 1;

               if (cnt_incr >= 15) incr = 10;
               if (cnt_incr >= 30) incr = 20;
               if (cnt_incr >= 45) incr = 30;
               if (cnt_incr >= 60) incr = 40;
               if (cnt_incr >= 90) incr = 45;

               for (i=0;i<50-incr;i++) { // Genero una pausa proporzionale
                  DisplayNum();          // a quanto ho incrementato i tempi
                  Delay_ms(1);
               }
               
             } // Fine del ciclo del tasto UP o DOWN

             if (PORTA.F1 == 1) { // Seconda pressione del tasto SET/STORE
                while (PORTA.F1 == 1) { DisplayNum(); } // Antirimbalzo
                uiSecondi_Fine = uiSecondi_Attuale;
                Salva_Sec(uiSecondi_Fine);
                break;
             }
             
           } // Fine del ciclo di SET/STORE
        } // Fine del tasto SET/STORE

     } // Fine del Loop Principale
}
