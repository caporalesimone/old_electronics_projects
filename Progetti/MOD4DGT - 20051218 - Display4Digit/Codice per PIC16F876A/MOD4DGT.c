//#define XTAL_FREQ 8MHZ
#define LEDNUM  PORTC
#define SEGMENTI PORTB

unsigned char NumDisplay;       //inizializzazione variabili
unsigned int temp,i;
unsigned int numero;
unsigned int valore;

char Unita;
char Decine;
char Centinaia;
char Migliaia;

void main(void)                 //Inizio programma
{
 LEDNUM = 0x00;                 //Spegne tutti i display
 TRISC=0;                       // setta porte C come uscita
 SEGMENTI = 0x00;               //mette a zero i display
 PORTB=0;
 TRISB = 0;
 NumDisplay = 1;                 //setta il contatore a 1

 i=0;
 numero=0;

 while(1)
 {
  Migliaia=0;                    //setto a zero le variabili
  Centinaia=0;
  Decine=0;
  Unita=0;

  i=numero;
  Temp=numero;

  if (((i/1000)>0) || (temp/10000)>0) Migliaia=((i/1000)+'0');   //Migliaia
  i-=(i/1000)*1000;

  if (((i/100)>0) || (temp/1000)>0) Centinaia=((i/100)+'0');    //Centinaia
  i-=(i/100)*100;

  if (((i/10)>0) || (temp/100)>0) Decine=((i/10)+'0');           //Decine
  i-=(i/10)*10;

  Unita = ((i/1)+'0');                                        //Unita

  LEDNUM = 0x00;                        //spengo i display
  switch(NumDisplay)                    //ciclo di visualzzazione dei 4 display
  {
   case 0:
        SEGMENTI=Unita;
        LEDNUM = 0x1;
   break;
   case 1:
        SEGMENTI=Decine;
        LEDNUM = 0x2;
   break;
   case 2:
        SEGMENTI=Centinaia;
        LEDNUM = 0x4;
   break;
   case 3:
        SEGMENTI=Migliaia;
        LEDNUM = 0x8;
  }
  NumDisplay=NumDisplay+1;
  if (NumDisplay==4) NumDisplay=0;

  numero++;
  if (numero>=10000) numero = 0;

  Delay_ms(1);

 }
}
