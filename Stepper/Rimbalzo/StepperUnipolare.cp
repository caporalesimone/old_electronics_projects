#line 1 "D:/pic/Stepper/Rimbalzo/StepperUnipolare.c"
#line 12 "D:/pic/Stepper/Rimbalzo/StepperUnipolare.c"
int step[8] = {1, 3, 2, 6,4,12,8,9};
int step2[] = {1, 2, 4, 8};

main() {

unsigned char e, dir;

 PORTA = 0x00;
 PORTB = 0x00;
 TRISA = 0x0F;
 TRISB = 0x000;

 e = 0;
 dir = 0;


 while (1) {

 if (dir == 0) {
 e = (e+1) % 4;
 PORTB = step2[e];
 Delay_ms( 10 );
 }

 if (dir != 0) {
 e = (e-1) % 4;
 PORTB = step2[e];
 Delay_ms( 10 );
 }

 if (PORTA == 0x01) {
 dir = 0;
 Delay_ms(100);
 }
 else if (PORTA == 0x08) {
 dir = 1;
 Delay_ms(100);
 }
 }
}
