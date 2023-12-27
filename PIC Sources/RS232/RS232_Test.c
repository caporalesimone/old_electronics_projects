

/*
void Usart_Write_String(char *str,unsigned int strlen) ;
unsigned int Usart_Get_Command (void);
void exec_command(unsigned int command);

*/

/*
unsigned int Usart_Get_Command (void)
{
 unsigned int j = 0;
 int i = -1;
 
 while (i != 13)
 {
  if (Usart_Data_Ready())
  {
   i = Usart_Read();         // Read the received data
   if ((i != 13) && (i != 10)) j = i;

   if (i != 10)
     Usart_Write(i);         // Send data via USART
  }
 }

 return j;
}
*/

void Usart_Write_String(char *str,unsigned int strlen)
{
 unsigned int i = 0;

 while (i<strlen)
 {
   Usart_Write(str[i]);
   i++;
 }
}

unsigned int Usart_Get_Command (void)
{
 int j;
 j = -1;

 while (j < 0){
  if (Usart_Data_Ready())
  {
   j = Usart_Read();       // Read the received data
   Usart_Write(j);         // Send data via USART
  }
 }
 return j;
}

void exec_command(unsigned int command)
{
 unsigned int i = command;
 int value;

 switch (i)
 {
  case 63: //Comando ?
  {
       Usart_Write_String("Command list : \n\n",17);
       Usart_Write(13);
       Usart_Write_String("? : Questo help\n",16);
       Usart_Write(13);
       Usart_Write_String("O : Gestione Output\n",20);
       Usart_Write(13);
       Usart_Write_String("R : Legge memoria I2C\n",22);
       Usart_Write(13);
       Usart_Write_String("\n",1);
       Usart_Write(13);
       break;
  }

  case 111: //Comando o
  {
       Usart_Write_String("0 -> Low\n",9);
       Usart_Write(13);
       Usart_Write_String("1 -> High\n",10);
       Usart_Write(13);
       Usart_Write_String(": ",2);

       value = Usart_Get_Command();
       Usart_Write_String("\n",1);
       Usart_Write(13);

       
       if (value == 48) //Tasto 0
         PORTA.F0 = 0;
       else
       {
        if (value == 49) //Tasto 1
          PORTA.F0 = 1;
        else
         {
          Usart_Write_String("ERRORE\n",7);
          Usart_Write(13);
         }
         
       }
       break;
  }




  case 118: //Comando v
  {
       /*Usart_Write_String("CSTech Operative System\n",24);
       Usart_Write_String("Version 1.0\n",12);
       Usart_Write_String("Compiled on 2005/04/23\n",23);
       Usart_Write_String("\n",1);*/
       break;
  }

  default :
  {
   Usart_Write_String("Comando non riconosciuto \n",27);
   Usart_Write(13);
   break;
  }

 } // END CASE
}



void main() {
  int j;

  TRISA = 0x00;      // Porta A settata in output;

  // Initialize USART module (8 bit, 2400 baud rate, no parity bit..)
  Usart_Init(56000);
  Usart_Write_String("CSTech Operative System 1.0\n\n",29);
  Usart_Write(13);
  //Usart_Write_String("#> ",3);
  

  
  do {
    //if (Usart_Data_Ready()) {   // If data is received
    Usart_Write_String("#> ",3);

    j = Usart_Get_Command();
    Usart_Write_String("\n",1);
    Usart_Write(13);

    exec_command(j);

  } while (1);
}//~!



