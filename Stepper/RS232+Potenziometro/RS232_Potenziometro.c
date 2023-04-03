
/*
  Il PIC 16F876A è collegato a un modulo dper la movimentazione
  di un motore passo passo.
  Il potenziometro seve per specificare il senso di rotazione e
  la velocità.
  Il PIC invia sulla porta RS232 il valore letto dal potenziometro.
  
  
  RA0 = Ingresso Analogico 0-5V
  
  RB0 = CLK Motore Passo Passo
  RB1 = Direzione Motore

*/



void main ()
{
  unsigned int iADC;
  char cValue;
  char clk;


  Usart_Init(9600);
  Sound_Init(&PORTB, 2);

  ADCON1 = 0x80;  // Configure analog inputs and Vref
  TRISA  = 0xFF;  // PORTA is input
  TRISB  = 0x00;  // Pins RB0, RB1 are outputs

  clk = 0;

  do {

    iADC = Adc_Read(0); // Get results of AD conversion
    cValue = iADC / 4 ;
    Usart_Write (cValue);
    Sound_Play(cValue, 10);
    delay_ms(8);
    
  /*  if ((cValue > 110) and (cvalue <  144))
    {

    } */

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









