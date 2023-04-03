/*
  Motore stepper unipolare
  Ruota a destra ed a sinistra cambiando direzione quando urta
  un finecorsa.
  
  


*/
#define asp 10                          //tempo di attesa in millisecondi
                                       //diminuire questo valore per aumentare la velocità
int step[8] = {1, 3, 2, 6,4,12,8,9};  //array per i mezzi passi
int step2[] = {1, 2, 4, 8};           //array per i passi interi

main() {

unsigned char e, dir;

 PORTA = 0x00;                         // azzera linee porta A
 PORTB = 0x00;                         // azzera linee porta B
 TRISA = 0x0F;                         // imposta linee porte A come ingressi
 TRISB = 0x000;                        // imposta linee porte B come uscite

 e = 0;                                // indice al primo elemento di step2
 dir = 0;                              // Indica la direzione di rotazione


 while (1) {                           // ciclo infinito

    if (dir == 0) {
       e = (e+1) % 4;         // modulo 4, ritorna un valore compreso tra 0 e 3
       PORTB = step2[e];               // pone PORTB con valore i-mo di step2
       Delay_ms(asp);                  // aspetta timeout
    }

    if (dir != 0) {
       e = (e-1) % 4;         // modulo 4, ritorna un valore compreso tra 0 e 3
       PORTB = step2[e];               // pone PORTB con valore i-mo di step2
       Delay_ms(asp);                  // aspetta timeout
    }

    if (PORTA == 0x01) {               // RA0 è down
       dir = 0;
       Delay_ms(100);
    }
    else if (PORTA == 0x08) {          // RA3 è down
       dir = 1;
       Delay_ms(100);
    }
 }
}
