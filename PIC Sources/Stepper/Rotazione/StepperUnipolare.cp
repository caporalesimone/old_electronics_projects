#line 1 "D:/pic/Stepper/Rotazione/StepperUnipolare.c"
#line 8 "D:/pic/Stepper/Rotazione/StepperUnipolare.c"
int step[8] = {1, 3, 2, 6,4,12,8,9};
int step2[] = {1, 2, 4, 8};

main() {

signed char i, e;

 PORTA = 0x00;
 PORTB = 0x00;
 TRISA = 0x0F;
 TRISB = 0x000;

 i=0;
 e=0;

 while (1) {
 while(PORTA == 0x01) {
 e = (e+1) % 4;
 PORTB = step2[e];
 Delay_ms( 4 );
 }
 while(PORTA == 0x02) {
 i = (i+1) % 8;
 PORTB = step[i];
 Delay_ms( 4 );
 }
 while(PORTA == 0x04) {
 i = (i-1) % 8;
 PORTB = step[i];
 Delay_ms( 4 );
 }
 while(PORTA == 0x08) {
 e = (e-1) % 4;
 PORTB = step2[e];
 Delay_ms( 4 );
 }
 }
}
