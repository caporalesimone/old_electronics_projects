#line 1 "D:/PIC/TimerBromografo/Timer.c"
#line 21 "D:/PIC/TimerBromografo/Timer.c"
unsigned char ucNumDisplay;
int uiSecondi_Attuale;
unsigned int uiSecondi_Fine;
unsigned char ucOutEnabled;

unsigned int uiContTmp;


void interrupt() {
 uiContTmp++;
 TMR0 = 96;
 INTCON = 0x20;
}


void DisplayNum (void) {
 unsigned char ucSecondi_Unita;
 unsigned char ucSecondi_Decine;
 unsigned char ucSecondi_Minuti;
 unsigned int uiSecondi;


 if (uiSecondi_Attuale > 0) {
 uiSecondi = uiSecondi_Attuale;

 ucSecondi_Minuti = uiSecondi / 60;
 uiSecondi = uiSecondi % 60;
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
 case 0:
  PORTB  = ucSecondi_Unita;
  PORTB  =  PORTB  + 16 + ucOutEnabled;
 break;
 case 1:
  PORTB  = ucSecondi_Decine;
  PORTB  =  PORTB  + 32 + ucOutEnabled;
 break;
 case 2:
  PORTB  = ucSecondi_Minuti;
  PORTB  =  PORTB  + 64 + ucOutEnabled;
 break;
 }
 ucNumDisplay++;
 if (ucNumDisplay >= 3) ucNumDisplay = 0;
}


void main (void) {
 char cEsciLoop;
 unsigned int i;
 unsigned char j,k;
 unsigned int uiMaxInterrupt;





 PORTB = 0;
 PORTA = 0;
 TRISA = 0xFF;
 TRISB = 0x00;


 OPTION_REG = 0x84;
 uiContTmp = 0;
 TMR0 = 96;





 uiSecondi_Fine = Eeprom_Read(1);
 Delay_ms(250);
 uiSecondi_Fine = uiSecondi_Fine + (256 * Eeprom_Read(3));
 if (uiSecondi_Fine >= 585) uiSecondi_Fine = 585;



 uiSecondi_Attuale = uiSecondi_Fine;
 ucOutEnabled = 0;

 uiMaxInterrupt = 187;

 while (1)
 {
 DisplayNum();


 if (PORTA.F0 == 0)
 {

 while (PORTA.F0 == 0) { }

 INTCON = 0xA0;
 uiSecondi_Attuale = uiSecondi_Fine;
 while (uiSecondi_Attuale > 0)
 {
 ucOutEnabled = 128;
 DisplayNum();

 if (uiContTmp >= uiMaxInterrupt)
 {
 uiSecondi_Attuale--;
 uiContTmp = 0;


 if (uiSecondi_Attuale < 120) uiMaxInterrupt = 180;
 }



 if ((PORTA.F0 == 0) && (uiSecondi_Attuale < uiSecondi_Fine - 5))
 {

 while (PORTA.F0 == 0) { }
 break;
 }
 }
 INTCON = 0x00;

 uiSecondi_Attuale = uiSecondi_Fine;
 ucOutEnabled = 0;
 }


 if (PORTA.F1 == 0)
 {
 cEsciLoop = 0;

 while (PORTA.F1 == 0) { }

 uiSecondi_Attuale = uiSecondi_Fine;

 while (cEsciLoop == 0)
 {
 DisplayNum();
 j = 0;
 k = 1;


 while (PORTA.F2 == 0)
 {
 j = j + k;
 if (j >= 10) k = 5;
 if (j >= 60) k = 30;


 for (i=0;i<50;i++) {
 DisplayNum();
 Delay_ms(1);
 }

 if (uiSecondi_Attuale + k < 599)
 uiSecondi_Attuale = uiSecondi_Attuale + k;
 else uiSecondi_Attuale = 1;

 for (i=0;i<50;i++) {
 DisplayNum();
 Delay_ms(1);
 }
 }


 while (PORTA.F3 == 0)
 {
 j = j + k;
 if (j >= 10) k = 5;
 if (j >= 60) k = 30;

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
 }


 if (PORTA.F1 == 0)
 {
 cEsciLoop = 1;

 while (PORTA.F1 == 0) { }

 uiSecondi_Fine = uiSecondi_Attuale;



 EEprom_Write(1, uiSecondi_Fine & 0b11111111);
 Delay_ms(250);
 EEprom_Write(3, uiSecondi_Fine / 0b11111111);
 }
 }
 }

 }
}
