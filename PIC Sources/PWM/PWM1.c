
void InitMain() {
  PORTB = 0;                     // set PORTB to 0
  TRISB = 0;                     // designate portb pins as output

  ADCON1 = 0x80;  // Configure analog inputs and Vref
  TRISA  = 0xFF;  // PORTA is input

  PORTC = 0x0;                   // set PORTC to $FF
  TRISC = 0;                     // designate PORTC pins as output
  PWM1_Init(20000);                // initialize PWM1 module
  PWM2_Init(20000);                // initialize PWM1 module                                                           PWM1_Init(5000);                // initialize PWM1 module
}

void main() {
  int i,j;

  initMain();


  PWM1_Start();                   // start PWM1
  PWM1_Change_Duty(127);        //    set new duty ratio,
  PWM2_Start();
  PWM2_Change_Duty(127);        //    set new duty ratio,
//  PWM1_Change_Duty(127);        //    set new duty ratio,
//  PWM2_Change_Duty(127);        //    set new duty ratio,
/*
  Delay_ms(2000);
  Delay_ms(2000);
  PWM1_Change_Duty(255);        //    set new duty ratio,
  PWM2_Change_Duty(255);        //    set new duty ratio,
  Delay_ms(2000);
  Delay_ms(2000);
*/

  Usart_Init(9600);

  while (1) {

  while (Usart_Data_Ready()==0) {}
  i = Usart_Read();
  while (Usart_Data_Ready()==0) {}
  j = Usart_Read();
  PWM1_Change_Duty(i);
  PWM2_Change_Duty(j);
    
    /*j = Usart_Read();
    if (i = 100) {  //Carattere d
       Usart_Write(100);
       PWM1_Change_Duty(j);
    }
    if (i = 115) {  //Carattere s
       Usart_Write(115);
       PWM2_Change_Duty(j);
    } */
  }
}
