#line 1 "D:/PIC/Timer_Led/TimerLed.c"
#line 18 "D:/PIC/Timer_Led/TimerLed.c"
unsigned char ucNumDisplay;
int uiSecondi_Attuale;
unsigned int uiSecondi_Fine;
unsigned char ucOutEnabled;

unsigned int uiContTmp;


void interrupt ()
{
 uiContTmp++;
 TMR0 = 96;
 INTCON = 0x20;
}


void InitMCU (void) {

 PORTB = 0;
 PORTA = 0;
 TRISA = 0xFF;
 TRISB = 0x00;


 OPTION_REG = 0x84;
 uiContTmp = 0;
 TMR0 = 96;
}


void Enable_Output (char OutEnabled){
 if (OutEnabled == 1)
 ucOutEnabled = 128;
 else
 ucOutEnabled = 0;
}


void Abilita_Timer (char TimerEnabled) {
 if (TimerEnabled == 1)
 INTCON = 0xA0;
 else
 INTCON = 0x00;
}

void DisplayNum (void)
{
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
 } else {
 ucSecondi_Minuti = 0;
 ucSecondi_Decine = 0;
 ucSecondi_Unita = 0;
 }

 switch(ucNumDisplay) {
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

int Carica_Sec(){
 int sec_letti;

 sec_letti = Eeprom_Read(1);
 Delay_ms(250);
 sec_letti = sec_letti + (256 * Eeprom_Read(3));
 return sec_letti;
}

void Salva_Sec(int Secondi){


 EEprom_Write(1, Secondi & 0b11111111);
 Delay_ms(250);
 EEprom_Write(3, Secondi / 0b11111111);
}

void main (void)
{
 unsigned int uiMaxInterrupt;
 unsigned int i;
 signed int incr;
 unsigned int cnt_incr;

 InitMCU();
 uiMaxInterrupt =  195 ;

 uiSecondi_Fine = Carica_Sec();
 if (uiSecondi_Fine >= 585) uiSecondi_Fine = 30;

 uiSecondi_Attuale = uiSecondi_Fine;

 Enable_Output(0);
 Abilita_Timer(1);


 while (1) {
 DisplayNum();

 if (PORTA.F0 == 1) {
 while (PORTA.F0 == 1) { DisplayNum(); }

 uiSecondi_Attuale = uiSecondi_Fine;
 Enable_Output(1);
 Abilita_Timer(1);

 while (uiSecondi_Attuale > 0) {
 DisplayNum();
 if (uiContTmp >= uiMaxInterrupt) {
 uiSecondi_Attuale--;
 uiContTmp = 0;


 }

 if ((PORTA.F0 == 1) && (uiSecondi_Attuale < uiSecondi_Fine - 3)){
 while (PORTA.F0 == 1) { DisplayNum(); }
 break;
 }
 }
 Enable_Output(0);
 Abilita_Timer(0);
 uiSecondi_Attuale = uiSecondi_Fine;
 Delay_ms(100);
 }

 if (PORTA.F1 == 1) {
 while (PORTA.F1 == 1) { DisplayNum(); }

 uiSecondi_Attuale = uiSecondi_Fine;

 while (1) {

 DisplayNum();
 Delay_ms(10);

 cnt_incr = 0;

 while ((PORTA.F2 == 1) || (PORTA.F3 == 1)) {

 DisplayNum();

 incr = 0;
 if (PORTA.F2 == 1) incr = 1;
 if (PORTA.F3 == 1) incr = -1;

 cnt_incr++;

 if ((uiSecondi_Attuale < 599) && (uiSecondi_Attuale >= 1))
 uiSecondi_Attuale = uiSecondi_Attuale + incr;
 else
 uiSecondi_Attuale = 1;

 if (cnt_incr >= 15) incr = 10;
 if (cnt_incr >= 30) incr = 20;
 if (cnt_incr >= 45) incr = 30;
 if (cnt_incr >= 60) incr = 40;
 if (cnt_incr >= 90) incr = 45;

 for (i=0;i<50-incr;i++) {
 DisplayNum();
 Delay_ms(1);
 }

 }

 if (PORTA.F1 == 1) {
 while (PORTA.F1 == 1) { DisplayNum(); }
 uiSecondi_Fine = uiSecondi_Attuale;
 Salva_Sec(uiSecondi_Fine);
 break;
 }

 }
 }

 }
}
