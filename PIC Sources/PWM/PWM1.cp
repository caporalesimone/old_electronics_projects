#line 1 "D:/PIC/PWM/PWM1.c"

void InitMain() {
 PORTB = 0;
 TRISB = 0;

 ADCON1 = 0x80;
 TRISA = 0xFF;

 PORTC = 0x0;
 TRISC = 0;
 PWM1_Init(20000);
 PWM2_Init(20000);
}

void main() {
 int i,j;

 initMain();


 PWM1_Start();
 PWM1_Change_Duty(127);
 PWM2_Start();
 PWM2_Change_Duty(127);
#line 36 "D:/PIC/PWM/PWM1.c"
 Usart_Init(9600);

 while (1) {

 while (Usart_Data_Ready()==0) {}
 i = Usart_Read();
 while (Usart_Data_Ready()==0) {}
 j = Usart_Read();
 PWM1_Change_Duty(i);
 PWM2_Change_Duty(j);
#line 56 "D:/PIC/PWM/PWM1.c"
 }
}
