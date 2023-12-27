#line 1 "D:/pic/Stepper/RS232+Potenziometro/RS232_Potenziometro.c"
#line 19 "D:/pic/Stepper/RS232+Potenziometro/RS232_Potenziometro.c"
void main ()
{
 unsigned int iADC;
 char cValue;
 char clk;


 Usart_Init(9600);
 Sound_Init(&PORTB, 2);

 ADCON1 = 0x80;
 TRISA = 0xFF;
 TRISB = 0x00;

 clk = 0;

 do {

 iADC = Adc_Read(0);
 cValue = iADC / 4 ;
 Usart_Write (cValue);
 Sound_Play(cValue, 10);
 delay_ms(8);
#line 48 "D:/pic/Stepper/RS232+Potenziometro/RS232_Potenziometro.c"
 if (cValue < 120)
 {
 portb.f1=0;
 portb.f0 = clk;
 if (clk == 1)
 clk = 0;
 else
 clk = 1;
 }

 if (cValue > 130)
 {
 portb.f1=1;
 portb.f0 = clk;
 if (clk == 1)
 clk = 0;
 else
 clk = 1;
 }


 } while(1);



}
