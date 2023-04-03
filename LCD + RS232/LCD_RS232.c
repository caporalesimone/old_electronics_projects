#define TMR0_RESET 131
#define TCK_SEC 312  //125 Per 8Mhz

const char txt_Avvio1[] = "CSTech";
const char txt_Avvio2[] = "Novembre 2006";

char *nomegrn[8]= {"Lun", "Mar", "Mer", "Gio", "Ven", "Sab", "Dom", "---"} ;

char txt_msg[15];

typedef struct {
  unsigned char hr;
  unsigned char min;
  unsigned char sec;
  unsigned char grn;
  unsigned int tck;
} tempo;

tempo ora;


//-------------- Copies constant string (in ROM) to 'normal' string (in RAM)
void strcp_c(char *str1, const char *cstr2) {
  unsigned short i = 0;

  do {
    str1[i] = cstr2[i];
  } while (str1[i++]);
}//~


// Invia una stringa alla seriale partendo dalla posizione start
void Usart_Write_Str(char *str ,int len, int start)
{
 int i;
 
 for (i=start; i<len; i++)
 {
  Usart_Write(str[i]);
 }

}


void interrupt()
{
   ora.tck++;
   TMR0 = TMR0_RESET;

   if (ora.tck == TCK_SEC) {
    ora.tck = 0;
    ora.sec++;
    if (ora.sec >= 60) {
     ora.sec = 0;
     ora.min++;
     if (ora.min >= 60) {
      ora.min=0;
      ora.hr++;
      if (ora.hr >= 24) {
       ora.hr = 0;
       ora.grn++;
       if (ora.grn == 7) ora.grn = 0;
      }
     }
    }
   }
   INTCON = 0x20;
}


void Init(void)
{
  // Init porte
  PORTB = 0;
  TRISB = 0xFF;
  PORTC = 0;
  TRISC = 0x0F;

  // Init timer TMR0
  OPTION_REG  = 0x86;       // RBPU_N + PS2-PS0
  TMR0        = TMR0_RESET;
  INTCON      = 0xA0;       // GIE + TMR0IE

  // Init display
  Lcd_Init(&PORTB);

  // Inizializzo la seriale
  Usart_Init(9600);

  // Init Ora
  ora.hr=0;
  ora.min=0;
  ora.sec=0;
  ora.tck=0;
  ora.grn=0;

  // Display del primo messaggio
  Lcd_Cmd(LCD_CLEAR);
  Lcd_Cmd(LCD_CURSOR_OFF);

  strcp_c(txt_msg, txt_Avvio1);
  LCD_Out(1,1,txt_msg);
  strcp_c(txt_msg, txt_Avvio2);
  LCD_Out(2,1,txt_msg);

  Delay_ms(1000);
  Lcd_Cmd(Lcd_CLEAR);       // Clear display

}

void Display_Ora () {

char thr[5],tmin[5],tsec[4];

     ByteToStr(ora.hr,thr);
     ByteToStr(ora.min,tmin);
     ByteToStr(ora.sec,tsec);

     if (thr[1]==' ') thr[1]='0';
     if (tmin[1]==' ') tmin[1]='0';
     if (tsec[1]==' ') tsec[1]='0';

     //strcp_c(txt_msg, nomegrn[ora.grn]);
     //LCD_Out(1,1,txt_msg);
     LCD_Out(1,1,nomegrn[ora.grn]);
     LCD_Out(1,5,(thr+1));
     Lcd_Chr_CP(':');
     LCD_Out(1,8,(tmin+1));
     Lcd_Chr_CP(':');
     LCD_Out(1,11,(tsec+1));

     LCD_Cmd(LCD_CURSOR_OFF);
}

void GestioneSeriale(char cmd)
{
 char thr[5],tmin[5],tsec[4];
 char dato;
 int i;

 switch (cmd) {
    case 49: // Richiesta l'ora (Tasto 1)

       ByteToStr(ora.hr,thr);
       ByteToStr(ora.min,tmin);
       ByteToStr(ora.sec,tsec);

       if (thr[1]==' ') thr[1]='0';
       if (tmin[1]==' ') tmin[1]='0';
       if (tsec[1]==' ') tsec[1]='0';

       Usart_Write_Str(nomegrn[ora.grn],3,0);
       Usart_Write_Str(thr,3,1);
       Usart_Write(':');
       Usart_Write_Str(tmin,3,1);
       Usart_Write(':');
       Usart_Write_Str(tsec,3,1);
    break;

    case 2: // Prepararsi ad un aggiornamento ora
       //gHMS

       while (!Usart_Data_Ready()) { asm nop; }
       ora.grn = Usart_Read();
       while (!Usart_Data_Ready()) { asm nop; }
       ora.hr  = Usart_Read();
       while (!Usart_Data_Ready()) { asm nop; }
       ora.min = Usart_Read();
       while (!Usart_Data_Ready()) { asm nop; }
       ora.sec = Usart_Read();

       ora.tck = 0;
    break;
 }
}

/*void I2C_Init()
{
  I2C_Init(400000);

}
*/

void main() {
int i;

  Init();
  //I2C_Init();
  Display_Ora();
  
  do {

     if (ora.tck == TCK_SEC-1)
          Display_Ora();

     if (Usart_Data_Ready()) {
        i = Usart_Read();
        //Usart_Write(i);
        GestioneSeriale(i);
     }

  } while (1);
}

