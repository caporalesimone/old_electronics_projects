/* 
* Programma di prova per LCD
*/

#include <pic.h>
#include <stdio.h>
#include "delay.c"
#define  valore 250
#include "lcd.c"

main()
{
       TRISB0=0;       //DATA 4 dell'LCD
       TRISB1=0;       //DATA 5
       TRISB2=0;       //DATA 6
       TRISB3=0;       //DATA 7
       TRISB4=0;       //RS
       TRISB5=0;       //E
       TRISA=1;         // setta le porte A del pic come entrate
       
       DelayMs(100);    // serve per stabilizzare l'alimentazione dell'lcd (l'lcd è molto lento)
   
       LCD_INIT(); // INDISPENSABILE serve ad inizializzare l'LCD
       DelayMs(250); // piccolo ritardo per completare l'inizializzazione (facoltativo)
       LCD_CLEAR(); // Cancella il display 
       DelayUs(200); // Altra piccola pausa   (facoltativo)

       LCD_CMD(LCD_line1);  //qui dico che devo cominciare a scrivere dal primo carattere del primo rigo
       LCD_PUTS("Primo programma LCD");  // ecco come si mette una stringa di caratteri

       LCD_CMD(LCD_line2);  //sposta il cursore alla prima posizione della seconda riga
       LCD_PUTS("valore assegnato:"); // altra stringa
       LCD_PUTUN(valore);    //numero già assegnato con define all'inizio del programma

       LCD_CMD(LCD_line3);  // terzo rigo
       LCD_PUTUN(valore);   // di nuovo il numero assegnato
       LCD_PUTS(" * 10/3 ="); // stringa di caratteri per far apparire l'operazione sul display
       LCD_PUTUN((valore*10)/3);  // fa il calcolo e scrive il risultato

 while(1)    // inizio ciclo
 {
  if(PORTA==0b00000001)   // verifica se viene premuto il tasto su RA0
  {  
   LCD_CMD(LCD_line4);  //quarto rigo
                  LCD_PUTS("tasto 1 premuto     ");  // stringa che appare se viene premuto il tasto su RA0
  }
  
  if(PORTA==0b00000010)   // verifica se viene premuto il tasto su RA1
  {  
   LCD_CMD(LCD_line4);  // quarto rigo, riposiziona il cursore alla prima posizione del quarto rigo
                  LCD_PUTS("tasto 2 premuto     ");  //stringa per il tasto su RA1
  }
 
  if(PORTA==0b00000000)   // verifica che non viene permuto nessun tasto
  {
   LCD_CMD(LCD_line4);   //riposiziona il cursore alla prima posizione del quarto rigo
                  LCD_PUTS("Nessun tasto premuto"); //stringa che appare se non viene premuto nessun tasto
  }  
}      
}

