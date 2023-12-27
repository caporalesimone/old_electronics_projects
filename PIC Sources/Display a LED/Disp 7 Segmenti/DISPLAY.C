#include<pic1684.h>
#include<delay.c>


/*

 Tabella di collegamento con un display a 7 segmenti

 RB0 = a                 a
 RB1 = b                ___
 RB2 = c               |   |
 RB3 = d              f|___|b
 RB4 = e               | g |
 RB5 = f              e|___|c 
 RB6 = g                 d

*/




// Definisco i valori dei led da accendere per ottenere un numero
int display[10] = {63,6,91,79,102,109,125,7,127,111};

void main()
{
 int i;

 TRISB=0;
 PORTB=0;

 i=0;
 for(;;)
 {
  PORTB=(display[i]);
  i++;
  if(i>9) i = 0;
  DelayMs(250);  	
 }

}
