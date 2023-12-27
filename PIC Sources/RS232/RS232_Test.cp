#line 1 "D:/pic/RS232/RS232_Test.c"
#line 32 "D:/pic/RS232/RS232_Test.c"
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
 j = Usart_Read();
 Usart_Write(j);
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
 case 63:
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

 case 111:
 {
 Usart_Write_String("0 -> Low\n",9);
 Usart_Write(13);
 Usart_Write_String("1 -> High\n",10);
 Usart_Write(13);
 Usart_Write_String(": ",2);

 value = Usart_Get_Command();
 Usart_Write_String("\n",1);
 Usart_Write(13);


 if (value == 48)
 PORTA.F0 = 0;
 else
 {
 if (value == 49)
 PORTA.F0 = 1;
 else
 {
 Usart_Write_String("ERRORE\n",7);
 Usart_Write(13);
 }

 }
 break;
 }




 case 118:
 {
#line 118 "D:/pic/RS232/RS232_Test.c"
 break;
 }

 default :
 {
 Usart_Write_String("Comando non riconosciuto \n",27);
 Usart_Write(13);
 break;
 }

 }
}



void main() {
 int j;

 TRISA = 0x00;


 Usart_Init(56000);
 Usart_Write_String("CSTech Operative System 1.0\n\n",29);
 Usart_Write(13);




 do {

 Usart_Write_String("#> ",3);

 j = Usart_Get_Command();
 Usart_Write_String("\n",1);
 Usart_Write(13);

 exec_command(j);

 } while (1);
}
