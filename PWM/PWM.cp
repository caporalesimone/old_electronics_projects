#line 1 "D:/PIC/PWM/PWM.c"
#line 22 "D:/PIC/PWM/PWM.c"
unsigned short j, oj;

void InitMain() {
 PORTB = 0;
 TRISB = 0;

 ADCON1 = 6;
 PORTA = 255;
 TRISA = 255;

 PORTC = 0x0;
 TRISC = 0;
 PWM1_Init(200000);
 PWM2_Init(200000);
}

void main() {
 initMain();

 j = 127;
 oj = 0;
 PWM1_Start();
 PWM2_Start();

 while (1) {
 if (Button(&PORTA, 0,1,1))
 j=j+10 ;
 if (Button(&PORTA, 1,1,1))
 j=j-10 ;

 if (oj != j) {
 PWM1_Change_Duty(j);
 PWM2_Change_Duty(j);
 oj = j;
 PORTB = oj;
 }
 Delay_ms(200);
 }
}
