

/******************************\
*                              *
*          DISPLAY             *
*                              *
*    (C) 2005 by Simone C.     *
*                              *
*    BIELLA IL  20-08-2005     *
*                              *
\******************************/

#include<pic1684.h>      

#include<delay.c>       

main(void)          
{
 int i = 0;	
 int pos = 0;
 TRISB = 0;          // setta le porte B come uscite
 while(1)               
 {
  PORTB = 0b00000001;
  pos = 0b00000001;
  DelayMs(250);	 
  for (i=0;i<6;i++)
  {
    pos=pos<<1;
    PORTB = pos;        // attiva RB1 (pin 7 del 16F84)
    DelayMs(250);     
  }
  pos = 0; 
 }
}
