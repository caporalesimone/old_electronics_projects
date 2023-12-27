#line 1 "D:/PIC/LCD + RS232/LCD_RS232.c"



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



void strcp_c(char *str1, const char *cstr2) {
 unsigned short i = 0;

 do {
 str1[i] = cstr2[i];
 } while (str1[i++]);
}



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
 TMR0 =  131 ;

 if (ora.tck ==  312 ) {
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

 PORTB = 0;
 TRISB = 0xFF;
 PORTC = 0;
 TRISC = 0x0F;


 OPTION_REG = 0x86;
 TMR0 =  131 ;
 INTCON = 0xA0;


 Lcd_Init(&PORTB);


 Usart_Init(9600);


 ora.hr=0;
 ora.min=0;
 ora.sec=0;
 ora.tck=0;
 ora.grn=0;


 Lcd_Cmd(LCD_CLEAR);
 Lcd_Cmd(LCD_CURSOR_OFF);

 strcp_c(txt_msg, txt_Avvio1);
 LCD_Out(1,1,txt_msg);
 strcp_c(txt_msg, txt_Avvio2);
 LCD_Out(2,1,txt_msg);

 Delay_ms(1000);
 Lcd_Cmd(Lcd_CLEAR);

}

void Display_Ora () {

char thr[5],tmin[5],tsec[4];

 ByteToStr(ora.hr,thr);
 ByteToStr(ora.min,tmin);
 ByteToStr(ora.sec,tsec);

 if (thr[1]==' ') thr[1]='0';
 if (tmin[1]==' ') tmin[1]='0';
 if (tsec[1]==' ') tsec[1]='0';



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
 case 49:

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

 case 2:


 while (!Usart_Data_Ready()) { asm nop; }
 ora.grn = Usart_Read();
 while (!Usart_Data_Ready()) { asm nop; }
 ora.hr = Usart_Read();
 while (!Usart_Data_Ready()) { asm nop; }
 ora.min = Usart_Read();
 while (!Usart_Data_Ready()) { asm nop; }
 ora.sec = Usart_Read();

 ora.tck = 0;
 break;
 }
}
#line 184 "D:/PIC/LCD + RS232/LCD_RS232.c"
void main() {
int i;

 Init();

 Display_Ora();

 do {

 if (ora.tck ==  312 -1)
 Display_Ora();

 if (Usart_Data_Ready()) {
 i = Usart_Read();

 GestioneSeriale(i);
 }

 } while (1);
}
