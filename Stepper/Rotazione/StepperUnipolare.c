/*
  Motore stepper unipolare


*/
#define asp 4                          //tempo di attesa in millisecondi
                                       //diminuire questo valore per aumentare la velocità
int step[8] = {1, 3, 2, 6,4,12,8,9};  //array per i mezzi passi
int step2[] = {1, 2, 4, 8};           //array per i passi interi

main() {

signed char i, e;                    // variabili indice

 PORTA = 0x00;                         // azzera linee porta A
 PORTB = 0x00;                         // azzera linee porta B
 TRISA = 0x0F;                         // imposta linee porte A come ingressi
 TRISB = 0x000;                        // imposta linee porte B come uscite

 i=0;                                // indice al primo elemento di step
 e=0;                                  // indice al primo elemento di step2

 while (1) {                           // ciclo infinito
    while(PORTA == 0x01) {             // ciclo fin quando RA0 è down
       e = (e+1) % 4;              // modulo 4, ritorna un valore compreso tra 0 e 3
       PORTB = step2[e];               // pone PORTB con valore i-mo di step2
       Delay_ms(asp);                  // aspetta timeout
    }
    while(PORTA == 0x02) {             // ciclo fin quando RA1 è down
       i = (i+1) % 8;               // modulo 8, ritorna un valore compreso tra 0 e 7
       PORTB = step[i];                // pone PORTB con valore i-mo di step
       Delay_ms(asp);                  // aspetta timeout
    }
    while(PORTA == 0x04) {             // ciclo fin quando RA2 è down
       i = (i-1) % 8;               // modulo 8, ritorna un valore compreso tra 0 e 7
       PORTB = step[i];                // pone PORTB con valore i-mo di step
       Delay_ms(asp);                  // aspetta timeout
    }
    while(PORTA == 0x08) {             // ciclo fin quando RA3 è down
       e = (e-1) % 4;              // modulo 4, ritorna un valore compreso tra 0 e 3
       PORTB = step2[e];               // pone PORTB con valore i-mo di step2
       Delay_ms(asp);                  // aspetta timeout
    }
 }
}
