#line 1 "D:/Elettronica/Progetti Completati/Display4Digit - MOD4DGT/Codice/MOD4DGT.c"




unsigned char NumDisplay;
unsigned int temp,i;
unsigned int numero;
unsigned int valore;

char Unita;
char Decine;
char Centinaia;
char Migliaia;

void main(void)
{
  PORTC  = 0x00;
 TRISC=0;
  PORTB  = 0x00;
 PORTB=0;
 TRISB = 0;
 NumDisplay = 1;

 i=0;
 numero=0;

 while(1)
 {
 Migliaia=0;
 Centinaia=0;
 Decine=0;
 Unita=0;

 i=numero;
 Temp=numero;

 if (((i/1000)>0) || (temp/10000)>0) Migliaia=((i/1000)+'0');
 i-=(i/1000)*1000;

 if (((i/100)>0) || (temp/1000)>0) Centinaia=((i/100)+'0');
 i-=(i/100)*100;

 if (((i/10)>0) || (temp/100)>0) Decine=((i/10)+'0');
 i-=(i/10)*10;

 Unita = ((i/1)+'0');

  PORTC  = 0x00;
 switch(NumDisplay)
 {
 case 0:
  PORTB =Unita;
  PORTC  = 0x1;
 break;
 case 1:
  PORTB =Decine;
  PORTC  = 0x2;
 break;
 case 2:
  PORTB =Centinaia;
  PORTC  = 0x4;
 break;
 case 3:
  PORTB =Migliaia;
  PORTC  = 0x8;
 }
 NumDisplay=NumDisplay+1;
 if (NumDisplay==4) NumDisplay=0;

 numero++;
 if (numero>=10000) numero = 0;

 Delay_ms(1);

 }
}
