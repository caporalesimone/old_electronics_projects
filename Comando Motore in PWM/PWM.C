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
 int k;
 char marcia;
 char premuto;
 char t_on;  // Durata impulso ON
 char t_off; // Durata impulso OFF
 

 PORTA=0;
 TRISA=0b00011;
 PORTB=0;
 TRISB=0;

 premuto=0;
 marcia=0;

 t_on=0;
 t_off=90;
 
 for(;;)
 {
   PORTB=(display[marcia]);
   if ((RA0==0) && (RA1==0)){
     premuto=0;	
   }
   
   if ((RA1==1) && (marcia<9) && (premuto==0))
   {
     marcia++;
     t_on=t_on+10;
     t_off=t_off-10;
     premuto=1;
   }

   if ((RA0==1) && (marcia>0) && (premuto==0))
   {
     marcia--;
     t_on=t_on-10;
     t_off=t_off+10;
     premuto=1;
   }

   RA2=1; // Impulso ON
   for (k=0;k<t_on;k++)
   {
     DelayUs(1);
   }

   RA2=0; // Impulso OFF
   for (k=0;k<t_off;k++)
   {
     DelayUs(1);
   }
   
 }

}
