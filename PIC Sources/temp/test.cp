#line 1 "D:/PIC/temp/test.c"




void make_delay(unsigned int delay){
int pausa;

 if (delay < 100)
 pausa = delay / 5;




 if ((delay >= 100) && (delay <= 200))
 pausa = 15;

 if ((delay >= 201) && (delay <= 300))
 pausa = 20;

 if ((delay >= 301) && (delay <= 400))
 pausa = 25;

 if ((delay >= 401) && (delay <= 500))
 pausa = 30;

 if ((delay >= 501) && (delay <= 600))
 pausa = 35;

 if ((delay >= 601) && (delay <= 700))
 pausa = 40;

 if ((delay >= 701) && (delay <= 800))
 pausa = 45;

 if ((delay >= 801) && (delay <= 900))
 pausa = 50;

 if (delay >= 901)
 pausa = 55;

 VDelay_ms (pausa);

}


void main() {
char enabled_motore_1 = 1;
char enabled_motore_2 = 1;

int delay = 0;

 ADCON1 = 0x80;
 PORTA = 255;
 TRISA = 255;
 PORTB = 0;
 TRISB = 0b11110000;
 PORTC = 0;
 TRISC = 0;

 while(1) {

 delay = Adc_Read(0) ;



 if ((PORTB.F6 == 0) && (PORTB.F7 == 0)){
 enabled_motore_1 = 0;
 PORTC.F1 = 0;
 }

 if (PORTB.F6 == 1) {
 enabled_motore_1 = 1;
 PORTB.F0 = 1;
 }

 if (PORTB.F7 == 1) {
 enabled_motore_1 = 1;
 PORTB.F0 = 0;
 }





 if ((PORTB.F4 == 0) && (PORTB.F5 == 0)){
 enabled_motore_2 = 0;
 PORTC.F2 = 0;
 }

 if (PORTB.F4 == 1) {
 enabled_motore_2 = 1;
 PORTB.F2 = 1;
 }

 if (PORTB.F5 == 1) {
 enabled_motore_2 = 1;
 PORTB.F2 = 0;
 }

 if ( (enabled_motore_1 == 1) || (enabled_motore_2 == 1) ){
 if (enabled_motore_1 == 1)
 PORTC.F1 = ~PORTC.F1;

 if (enabled_motore_2 == 1)
 PORTC.F2 = ~PORTC.F2;

 make_delay(delay);
 }





 }
}
