/* 

Mongrando 28-Agosto-2005



Testo scorrevole per il display LCD 1x16
(N.B. Funziona come un 2x8)



B0-B3 sono i segnali per LCD D4-D8
B4 Š il segnale RS
B5 Š il segnale E

A0 Š settato in input e gestisce
   la direzione dello scorrimento del testo


*/

#include <pic1684.h>
#include <stdio.h>
#include <string.h>
#include "delay.c"
#include "lcd.c"


char str1[8];
char str2[8];



void l_shift()
{
  char tmp;
  int len;
  int i;

  //len = strlen(str1)-1;
  len=7;
  tmp = str1[0];
  
  for (i=0; i < len; i++)
  {
    str1[i] = str1[i+1];
  }

  str1[len] = str2[0];

  for (i=0; i < len; i++)
  {
    str2[i] = str2[i+1];
  }

  str2[len] = tmp;	
 	
}



void r_shift()
{
  char tmp;
  int len;
  int i;

  //len = strlen(str2);
  len=7;
  tmp = str2[len];

  for (i=len;i>0;i--)
  {
    str2[i] = str2[i-1];  
  }
	   
  str2[0] = str1[len];

  for (i=len;i>0;i--)
  {
    str1[i] = str1[i-1];  
  }

  str1[0] = tmp;

}



main()
{

  strcpy(str1,"Tanti au");  
  strcpy(str2,"guri!!..");
	
  TRISB0=0;       //DATA 4 dell'LCD
  TRISB1=0;       //DATA 5
  TRISB2=0;       //DATA 6
  TRISB3=0;       //DATA 7
  TRISB4=0;       //RS
  TRISB5=0;       //E

  TRISA0=1;       // Direzione 
       

  DelayMs(250);    // serve per stabilizzare l'alimentazione dell'lcd (l'lcd è molto lento)

   
  LCD_INIT(); // INDISPENSABILE serve ad inizializzare l'LCD
  DelayMs(250); // piccolo ritardo per completare l'inizializzazione

  LCD_CLEAR(); // Cancella il display 
  DelayMs(250); // Altra piccola pausa  
      

  LCD_GOTO(1,1);
  LCD_PUTS(str1);
  LCD_GOTO(2,1);
  LCD_PUTS(str2);

      
  while (1)
  {
     
   DelayMs(250);       


   if(PORTA == 0b00000001)
    {
     r_shift();
    }
   else
    {
     l_shift();
    }
	        

   LCD_GOTO(1,1);
   LCD_PUTS(str1);
   LCD_GOTO(2,1);
   LCD_PUTS(str2);
  }
     
}

