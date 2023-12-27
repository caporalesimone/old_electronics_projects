
_LCD_Out_const:

;Sensore Distanza.c,27 :: 		void LCD_Out_const(char x, char y, const char *txt){
;Sensore Distanza.c,31 :: 		dst = loc_text;
	MOVLW       LCD_Out_const_loc_text_L0+0
	MOVWF       LCD_Out_const_dst_L0+0 
	MOVLW       hi_addr(LCD_Out_const_loc_text_L0+0)
	MOVWF       LCD_Out_const_dst_L0+1 
;Sensore Distanza.c,32 :: 		while (*dst++ = *txt++);
L_LCD_Out_const0:
	MOVF        LCD_Out_const_dst_L0+0, 0 
	MOVWF       R3 
	MOVF        LCD_Out_const_dst_L0+1, 0 
	MOVWF       R4 
	INFSNZ      LCD_Out_const_dst_L0+0, 1 
	INCF        LCD_Out_const_dst_L0+1, 1 
	MOVF        FARG_LCD_Out_const_txt+0, 0 
	MOVWF       R0 
	MOVF        FARG_LCD_Out_const_txt+1, 0 
	MOVWF       R1 
	MOVF        FARG_LCD_Out_const_txt+2, 0 
	MOVWF       R2 
	MOVLW       1
	ADDWF       FARG_LCD_Out_const_txt+0, 1 
	MOVLW       0
	ADDWFC      FARG_LCD_Out_const_txt+1, 1 
	ADDWFC      FARG_LCD_Out_const_txt+2, 1 
	MOVF        R0, 0 
	MOVWF       TBLPTRL 
	MOVF        R1, 0 
	MOVWF       TBLPTRH 
	MOVF        R2, 0 
	MOVWF       TBLPTRU 
	TBLRD*+
	MOVFF       TABLAT+0, R0
	MOVFF       R3, FSR1
	MOVFF       R4, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVFF       R3, FSR0
	MOVFF       R4, FSR0H
	MOVF        POSTINC0+0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_LCD_Out_const1
	GOTO        L_LCD_Out_const0
L_LCD_Out_const1:
;Sensore Distanza.c,34 :: 		LCD_Out(x, y, loc_text);
	MOVF        FARG_LCD_Out_const_x+0, 0 
	MOVWF       FARG_Lcd_Out_row+0 
	MOVF        FARG_LCD_Out_const_y+0, 0 
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       LCD_Out_const_loc_text_L0+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(LCD_Out_const_loc_text_L0+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;Sensore Distanza.c,35 :: 		}
L_end_LCD_Out_const:
	RETURN      0
; end of _LCD_Out_const

_interrupt:

;Sensore Distanza.c,37 :: 		void interrupt(){              // Interrupt rutine
;Sensore Distanza.c,54 :: 		}
L_end_interrupt:
L__interrupt12:
	RETFIE      1
; end of _interrupt

_hardware_default_setup:

;Sensore Distanza.c,59 :: 		void hardware_default_setup (void) {
;Sensore Distanza.c,61 :: 		INTCON = 0x00; // Disabilita tutti gli interrupt. Verranno settati dopo
	CLRF        INTCON+0 
;Sensore Distanza.c,62 :: 		PIE1 = 0x00;   // Peripheral interrupt enable bits
	CLRF        PIE1+0 
;Sensore Distanza.c,63 :: 		PIE2 = 0x00;   // Peripheral interrupt enable bits
	CLRF        PIE2+0 
;Sensore Distanza.c,64 :: 		PIR1 = 0x00;   // Peripheral interrupt flag bits
	CLRF        PIR1+0 
;Sensore Distanza.c,65 :: 		PIR2 = 0x00;   // Peripheral interrupt flag bits
	CLRF        PIR2+0 
;Sensore Distanza.c,66 :: 		IPR1 = 0x00;   // Interrupt priority LOW
	CLRF        IPR1+0 
;Sensore Distanza.c,67 :: 		IPR2 = 0x00;   // Interrupt priority LOW
	CLRF        IPR2+0 
;Sensore Distanza.c,68 :: 		CMCON  |= 7;   // Disable comparators
	MOVLW       7
	IORWF       CMCON+0, 1 
;Sensore Distanza.c,70 :: 		ADCON0 = 0x00;       // ADC disabilitato
	CLRF        ADCON0+0 
;Sensore Distanza.c,71 :: 		ADCON1 = 0b00001111; // Configura tuttu i pin AN come digitali
	MOVLW       15
	MOVWF       ADCON1+0 
;Sensore Distanza.c,73 :: 		TRISA = 0xFF; // Setta la PORTA tutta in input
	MOVLW       255
	MOVWF       TRISA+0 
;Sensore Distanza.c,74 :: 		TRISB = 0xFF; // Setta la PORTB tutta in input
	MOVLW       255
	MOVWF       TRISB+0 
;Sensore Distanza.c,75 :: 		TRISC = 0xFF; // Setta la PORTC tutta in input
	MOVLW       255
	MOVWF       TRISC+0 
;Sensore Distanza.c,76 :: 		TRISD = 0xFF; // Setta la PORTD tutta in input
	MOVLW       255
	MOVWF       TRISD+0 
;Sensore Distanza.c,77 :: 		TRISE = 0xFF; // Setta la PORTE tutta in input
	MOVLW       255
	MOVWF       TRISE+0 
;Sensore Distanza.c,78 :: 		}
L_end_hardware_default_setup:
	RETURN      0
; end of _hardware_default_setup

_hardware_specific_setup:

;Sensore Distanza.c,81 :: 		void hardware_specific_setup (void) {
;Sensore Distanza.c,83 :: 		TRISD = 0b00000011; // Setta in output pin della porta D utilizzati dal Display
	MOVLW       3
	MOVWF       TRISD+0 
;Sensore Distanza.c,92 :: 		}
L_end_hardware_specific_setup:
	RETURN      0
; end of _hardware_specific_setup

_main:

;Sensore Distanza.c,95 :: 		void main(void) {
;Sensore Distanza.c,97 :: 		char uart_rd = 0;
;Sensore Distanza.c,101 :: 		hardware_default_setup();    // Inizializzazione di default della MCU
	CALL        _hardware_default_setup+0, 0
;Sensore Distanza.c,102 :: 		hardware_specific_setup();   // Inizializzazione specifica per questa applicazione
	CALL        _hardware_specific_setup+0, 0
;Sensore Distanza.c,103 :: 		Delay_ms(10);
	MOVLW       65
	MOVWF       R12, 0
	MOVLW       238
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	NOP
;Sensore Distanza.c,104 :: 		Lcd_Init();                  // Inizializza il display LCD
	CALL        _Lcd_Init+0, 0
;Sensore Distanza.c,106 :: 		Lcd_Cmd(_LCD_CLEAR);         // Clear display
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Sensore Distanza.c,107 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);    // Cursor off
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Sensore Distanza.c,108 :: 		LCD_Out_const(1,1,txt_start1);
	MOVLW       1
	MOVWF       FARG_LCD_Out_const_x+0 
	MOVLW       1
	MOVWF       FARG_LCD_Out_const_y+0 
	MOVLW       _txt_start1+0
	MOVWF       FARG_LCD_Out_const_txt+0 
	MOVLW       hi_addr(_txt_start1+0)
	MOVWF       FARG_LCD_Out_const_txt+1 
	MOVLW       higher_addr(_txt_start1+0)
	MOVWF       FARG_LCD_Out_const_txt+2 
	CALL        _LCD_Out_const+0, 0
;Sensore Distanza.c,109 :: 		LCD_Out_const(2,1,txt_start2);
	MOVLW       2
	MOVWF       FARG_LCD_Out_const_x+0 
	MOVLW       1
	MOVWF       FARG_LCD_Out_const_y+0 
	MOVLW       _txt_start2+0
	MOVWF       FARG_LCD_Out_const_txt+0 
	MOVLW       hi_addr(_txt_start2+0)
	MOVWF       FARG_LCD_Out_const_txt+1 
	MOVLW       higher_addr(_txt_start2+0)
	MOVWF       FARG_LCD_Out_const_txt+2 
	CALL        _LCD_Out_const+0, 0
;Sensore Distanza.c,111 :: 		Delay_ms(3000);
	MOVLW       77
	MOVWF       R11, 0
	MOVLW       25
	MOVWF       R12, 0
	MOVLW       79
	MOVWF       R13, 0
L_main3:
	DECFSZ      R13, 1, 1
	BRA         L_main3
	DECFSZ      R12, 1, 1
	BRA         L_main3
	DECFSZ      R11, 1, 1
	BRA         L_main3
	NOP
	NOP
;Sensore Distanza.c,113 :: 		Lcd_Cmd(_LCD_CLEAR);         // Clear display
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Sensore Distanza.c,115 :: 		UART1_Init(115200);            // Initialize UART module at 9600 bps
	BSF         BAUDCON+0, 3, 0
	CLRF        SPBRGH+0 
	MOVLW       42
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;Sensore Distanza.c,116 :: 		Delay_ms(100);               // Wait for UART module to stabilize
	MOVLW       3
	MOVWF       R11, 0
	MOVLW       138
	MOVWF       R12, 0
	MOVLW       85
	MOVWF       R13, 0
L_main4:
	DECFSZ      R13, 1, 1
	BRA         L_main4
	DECFSZ      R12, 1, 1
	BRA         L_main4
	DECFSZ      R11, 1, 1
	BRA         L_main4
	NOP
	NOP
;Sensore Distanza.c,118 :: 		UART1_Write_Text("Start");
	MOVLW       ?lstr1_Sensore_32Distanza+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr1_Sensore_32Distanza+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;Sensore Distanza.c,119 :: 		UART1_Write(10);
	MOVLW       10
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;Sensore Distanza.c,120 :: 		UART1_Write(13);
	MOVLW       13
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;Sensore Distanza.c,122 :: 		x = 1;
	MOVLW       1
	MOVWF       main_x_L0+0 
;Sensore Distanza.c,123 :: 		y = 1;
	MOVLW       1
	MOVWF       main_y_L0+0 
;Sensore Distanza.c,124 :: 		while (1) {                     // Endless loop
L_main5:
;Sensore Distanza.c,125 :: 		if (UART1_Data_Ready()) {     // If data is received,
	CALL        _UART1_Data_Ready+0, 0
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main7
;Sensore Distanza.c,126 :: 		uart_rd = UART1_Read();     // read the received data
	CALL        _UART1_Read+0, 0
;Sensore Distanza.c,127 :: 		Lcd_Chr(y,x,uart_rd);
	MOVF        main_y_L0+0, 0 
	MOVWF       FARG_Lcd_Chr_row+0 
	MOVF        main_x_L0+0, 0 
	MOVWF       FARG_Lcd_Chr_column+0 
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Chr_out_char+0 
	CALL        _Lcd_Chr+0, 0
;Sensore Distanza.c,129 :: 		sprinti(out_str,"X=%d",(int)x);
	MOVLW       main_out_str_L0+0
	MOVWF       FARG_sprinti_wh+0 
	MOVLW       hi_addr(main_out_str_L0+0)
	MOVWF       FARG_sprinti_wh+1 
	MOVLW       ?lstr_2_Sensore_32Distanza+0
	MOVWF       FARG_sprinti_f+0 
	MOVLW       hi_addr(?lstr_2_Sensore_32Distanza+0)
	MOVWF       FARG_sprinti_f+1 
	MOVLW       higher_addr(?lstr_2_Sensore_32Distanza+0)
	MOVWF       FARG_sprinti_f+2 
	MOVF        main_x_L0+0, 0 
	MOVWF       FARG_sprinti_wh+5 
	MOVLW       0
	MOVWF       FARG_sprinti_wh+6 
	CALL        _sprinti+0, 0
;Sensore Distanza.c,130 :: 		UART1_Write_Text(out_str);
	MOVLW       main_out_str_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(main_out_str_L0+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;Sensore Distanza.c,131 :: 		sprinti(out_str," - Y=%d\r\n",(int)y);
	MOVLW       main_out_str_L0+0
	MOVWF       FARG_sprinti_wh+0 
	MOVLW       hi_addr(main_out_str_L0+0)
	MOVWF       FARG_sprinti_wh+1 
	MOVLW       ?lstr_3_Sensore_32Distanza+0
	MOVWF       FARG_sprinti_f+0 
	MOVLW       hi_addr(?lstr_3_Sensore_32Distanza+0)
	MOVWF       FARG_sprinti_f+1 
	MOVLW       higher_addr(?lstr_3_Sensore_32Distanza+0)
	MOVWF       FARG_sprinti_f+2 
	MOVF        main_y_L0+0, 0 
	MOVWF       FARG_sprinti_wh+5 
	MOVLW       0
	MOVWF       FARG_sprinti_wh+6 
	CALL        _sprinti+0, 0
;Sensore Distanza.c,132 :: 		UART1_Write_Text(out_str);
	MOVLW       main_out_str_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(main_out_str_L0+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;Sensore Distanza.c,134 :: 		x++;
	INCF        main_x_L0+0, 1 
;Sensore Distanza.c,136 :: 		if (x == 17) {
	MOVF        main_x_L0+0, 0 
	XORLW       17
	BTFSS       STATUS+0, 2 
	GOTO        L_main8
;Sensore Distanza.c,137 :: 		x = 1;
	MOVLW       1
	MOVWF       main_x_L0+0 
;Sensore Distanza.c,138 :: 		y++;
	INCF        main_y_L0+0, 1 
;Sensore Distanza.c,139 :: 		if (y == 3) {
	MOVF        main_y_L0+0, 0 
	XORLW       3
	BTFSS       STATUS+0, 2 
	GOTO        L_main9
;Sensore Distanza.c,140 :: 		x = 1;
	MOVLW       1
	MOVWF       main_x_L0+0 
;Sensore Distanza.c,141 :: 		y = 1;
	MOVLW       1
	MOVWF       main_y_L0+0 
;Sensore Distanza.c,142 :: 		Lcd_Cmd(_LCD_CLEAR);         // Clear display
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;Sensore Distanza.c,143 :: 		}
L_main9:
;Sensore Distanza.c,144 :: 		}
L_main8:
;Sensore Distanza.c,145 :: 		}
L_main7:
;Sensore Distanza.c,146 :: 		}
	GOTO        L_main5
;Sensore Distanza.c,149 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
