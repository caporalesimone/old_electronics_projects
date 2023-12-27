/*

Comando 2 display ad anodo comune

RA2 e RA3 abilitano i transistor che alimentano l'anodo
RB0-RB6 Sono i segnali che contengono i valori

*/


#include<pic1687x.h>
#include<delay.c>


// Definisco i valori dei led da accendere per ottenere un numero

int display[10] = {63,6,91,79,102,109,125,7,127,111};

void main()
{
 int i;
 int unita;
 int decine;


 PORTB=0;
 TRISB=0;
 PORTA=0;
 TRISA=0;

 unita=0;
 decine=0;
 i=0;

 for(;;)
 {

   for (i=0;i<50;i++)
   {
     PORTA=0b000100;
     PORTB=255-(display[unita]);
     DelayMs(1);
     PORTA=0b001000;
     PORTB=255-(display[decine]);
     DelayMs(1);
   }

   unita++;
   if(unita>9) {
     unita=0;
     decine++;
   }

   if (decine>9) {
     unita=0;
     decine=0;
   }
 }
}
