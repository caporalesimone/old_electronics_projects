#line 1 "D:/PIC/MonitorCaricaBatteria/MonitorCaricaBatterie.c"
#line 46 "D:/PIC/MonitorCaricaBatteria/MonitorCaricaBatterie.c"
const char txt_avvio1[] = "Monitor Batteria";
const char txt_avvio2[] = "CSTech  Set 2007";
const char txt_avvio3[] = "Firmware  v 2.06";
const char txt_avvio4[] = "________________";

const char txt_riga1[] = "AUDI    :   .  V";
const char txt_riga2[] = "MERCEDES:   .  V";

unsigned int intCont = 1;
char lcd_light_status =  1 ;



void lcd_set_light(char status)
{
 intCont = 1;
 if (status ==  0 ) {
 PORTA.F4 =  0 ;
 lcd_light_status =  0 ;
 } else {
 PORTA.F4 =  1 ;
 lcd_light_status =  1 ;
 }
}



void rom_str2lcd (unsigned char riga, unsigned char col ,char const *str_in_ROM)
{
 unsigned short i = 0;
 char txt_msg[16];

 do {
 txt_msg[i] = str_in_ROM[i];
 } while (str_in_ROM[i++]);

 LCD_Out(riga,col,txt_msg);
}



void init_MCU (void)
{
 INTCON = 0;

 ADCON1 = 0b11000100;


 TRISA = 0b11101111;
 TRISB = 0x00;
 TRISC = 0x00;
}



void start_LCD()
{
 Lcd_Init(&PORTB);
 Delay_ms(5);
 Lcd_Cmd(LCD_CLEAR);
 Delay_ms(5);
 Lcd_Cmd(LCD_CURSOR_OFF);
 Delay_ms(250);
}



void Display_Tensione(unsigned int adcVolt1, unsigned int adcVolt2)
{
 long tensione1;
 long tensione2;
 unsigned char ch;

 tensione1 = ( 1650  * (unsigned long)adcVolt1) / 1023;
 tensione2 = ( 1650  * (unsigned long)adcVolt2) / 1023;




 Usart_Write('[');
 ch = tensione1 / 1000;
 Usart_Write(ch);
 LCD_Chr(1,11,48+ch);
 ch = (tensione1 / 100) % 10;
 Usart_Write(ch);
 LCD_Chr_CP(48+ch);
 LCD_Chr_CP('.');
 ch = (tensione1 / 10) % 10;
 Usart_Write(ch);
 LCD_Chr_CP(48+ch);
 ch = tensione1 % 10;
 Usart_Write(ch);
 LCD_Chr_CP(48+ch);


 ch = tensione2 / 1000;
 Usart_Write(ch);
 LCD_Chr(2,11,48+ch);
 ch = (tensione2 / 100) % 10;
 Usart_Write(ch);
 LCD_Chr_CP(48+ch);
 LCD_Chr_CP('.');
 ch = (tensione2 / 10) % 10;
 Usart_Write(ch);
 LCD_Chr_CP(48+ch);
 ch = tensione2 % 10;
 Usart_Write(ch);
 LCD_Chr_CP(48+ch);

 Usart_Write(']');
#line 180 "D:/PIC/MonitorCaricaBatteria/MonitorCaricaBatterie.c"
}


void Display_Info(void){
 rom_str2lcd(1,1,txt_avvio1);
 rom_str2lcd(2,1,txt_avvio2);
 Delay_ms(2000);
 rom_str2lcd(1,1,txt_avvio3);
 rom_str2lcd(2,1,txt_avvio4);
 Delay_ms(2000);
 Lcd_Cmd(Lcd_CLEAR);
}

void main ()
{
 unsigned long int adc_volt1;
 unsigned long int adc_volt2;

 int i;



 init_MCU();
 lcd_set_light( 1 );
 start_LCD();

 Display_Info();

 rom_str2lcd(1,1,txt_riga1);
 rom_str2lcd(2,1,txt_riga2);

 USART_Init(9600);

 while (1)
 {



 if (lcd_light_status ==  1 ) {
 intCont++;
 if (intCont >=  126 ){
 lcd_set_light( 0 );
 }
 }

 adc_volt1 = 0;
 adc_volt2 = 0;

 for (i=0;i< 400 ;i++){
 adc_volt1 = adc_volt1 + ADC_read(0);
 adc_volt2 = adc_volt2 + ADC_read(1);
 Delay_ms( 1 );


 if (PORTA.F2 ==  1 ) {
 Delay_ms(500);
 while (PORTA.F2 ==  1 ) { }
 if (lcd_light_status ==  1 ) {
 lcd_set_light( 0 );
 } else {
 lcd_set_light( 1 );
 }
 }
 }

 adc_volt1 = adc_volt1 /  400 ;
 adc_volt2 = adc_volt2 /  400 ;

 Display_Tensione (adc_volt1, adc_volt2);
 }

}
