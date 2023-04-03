/* 
* Fiser termometer
* usa un LM35 collegato alla porta RA1 del 16F876/877
* visualizza la temperatura in Celsius, Fahrenheit e Kelvin
* utilizza le routine lcd di Andrea Bronzini
* (c) 2003 by Fiocco Sergio 
*/

#include <pic1687x.h>
#include <stdio.h>
#define  XTAL_FREQ 4MHZ
#include "delay.c"
#include "lcd.c"


#define NCAMPIONI 10

main()
{
int valore; 
float valore1;
float mediavolt;
float mediatemp;
int i;


       TRISB0=0;       //DATA 4
       TRISB1=0;       //DATA 5
       TRISB2=0;       //DATA 6
       TRISB3=0;       //DATA 7
       TRISB4=0;       //RS
       TRISB5=0;       //E
       TRISC=0;        //PORTC tutte uscite
       PORTC=0;        //PORTC tutte a 0

       DelayMs(20);      
       LCD_INIT();     //inizializza l'lcd
       DelayMs(50);
       LCD_CLEAR();    //pulisce lo schermo lcd
       DelayUs(20);

      
       ADCON0 = 0b11000001;                  //abilita AD
       ADCON1 = 0b10000000;  
       
       LCD_PUTS("Attendere prego...");

       mediatemp=0;
       mediavolt=0; 

                     
       for(;;) 
       {
          
          for (i=0;i<NCAMPIONI;i++)
          {
             ADGO = 1;                         //Fa partire la conversione
             while(ADGO)
               continue;                         //Attende la conversione

               valore = ADRESL+(ADRESH<<8);      //risultato in valore
               mediatemp = mediatemp + (float)((valore/2.0)-273.15)*10;   
               mediavolt = mediavolt + (float)valore/20;
                
               DelayMs(250);
	       DelayMs(250);
               LCD_GOTO(2,1);
               LCD_PUTUN(i*10);
               LCD_PUTS("%");
          }      
           LCD_CLEAR(); 
           valore1 = mediatemp/NCAMPIONI;          


           if(valore1>197)
           {
              RC1=1;  // Abilita una uscita per attivare qualcosa
           }
           else
              {
	        if(valore1<191)
                   RC1=0;
              }
           
           LCD_PUTUN((unsigned int)valore1/10);
           LCD_PUTS(",");
           LCD_PUTUN((unsigned int)valore1%10);
           LCD_PUTCH(0b11011111);
           LCD_PUTS("C   ");

           valore1=mediavolt/NCAMPIONI; 
           LCD_PUTUN((unsigned int)valore1/10);
           LCD_PUTS(",");
           LCD_PUTUN((unsigned int)valore1%10);
           //LCD_PUTUN((unsigned int)valore1%100);
           LCD_PUTS("V");

           LCD_GOTO(2,5);
           LCD_PUTS("Ventola ");
           if(RC1==1)
	     LCD_PUTS("ON");
	   else
	     LCD_PUTS("OFF");  
           

           DelayMs(250);
 
           mediatemp=0;
           mediavolt=0; 

       
           }
      
}
