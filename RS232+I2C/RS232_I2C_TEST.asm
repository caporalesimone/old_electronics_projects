;  ASM code generated by mikroVirtualMachine for PIC - V. 3.0.0.0
;  Date/Time: 25/04/2006 14.07.06
;  Info: http://www.mikroelektronika.co.yu


; ADDRESS	OPCODE	ASM
; ----------------------------------------------
$0000	$2844	GOTO	_main
$0004	$	_Usart_Init:
$0004	$1303	BCF	STATUS,RP1
$0005	$1683	BSF	STATUS,RP0
$0006	$1698	BSF	TXSTA,5
$0007	$3090	MOVLW	144
$0008	$1283	BCF	STATUS,RP0
$0009	$0098	MOVWF 	RCSTA
$000A	$1683	BSF	STATUS,RP0
$000B	$1787	BSF	TRISC,7
$000C	$1307	BCF	TRISC,6
$000D	$	L_Usart_Init_0:
$000D	$01F0	CLRF 	STACK_0
$000E	$01F1	CLRF	STACK_1
$000F	$1283	BCF	STATUS,RP0
$0010	$1A8C	BTFSC	PIR1,5
$0011	$0AF1	INCF	STACK_1,F
$0012	$0871	MOVF	STACK_1,W
$0013	$0270	SUBWF	STACK_0,W
$0014	$1903	BTFSC	STATUS,Z
$0015	$2819	GOTO 	L_Usart_Init_1
$0016	$081A	MOVF 	RCREG,W
$0017	$00A1	MOVWF 	Usart_Init_tmp_L0
$0018	$280D	GOTO 	L_Usart_Init_0
$0019	$	L_Usart_Init_1:
$0019	$0008	RETURN
$001A	$	_Usart_Data_Ready:
$001A	$1303	BCF	STATUS,RP1
$001B	$1283	BCF	STATUS,RP0
$001C	$01F0	CLRF	STACK_0
$001D	$1A8C	BTFSC	PIR1,5
$001E	$0AF0	INCF	STACK_0,F
$001F	$0870	MOVF 	STACK_0,W
$0020	$00A1	MOVWF 	_Usart_Data_Ready_local_result
$0021	$0008	RETURN 
$0022	$	_Usart_Read:
$0022	$1303	BCF	STATUS,RP1
$0023	$1283	BCF	STATUS,RP0
$0024	$081A	MOVF 	RCREG,W
$0025	$00A2	MOVWF 	Usart_Read_tmp_L0
$0026	$01F0	CLRF 	STACK_0
$0027	$01F1	CLRF	STACK_1
$0028	$1898	BTFSC	RCSTA,1
$0029	$0AF1	INCF	STACK_1,F
$002A	$0871	MOVF	STACK_1,W
$002B	$0270	SUBWF	STACK_0,W
$002C	$1903	BTFSC	STATUS,Z
$002D	$2830	GOTO 	L_Usart_Read_2
$002E	$1218	BCF	RCSTA,4
$002F	$1618	BSF	RCSTA,4
$0030	$	L_Usart_Read_2:
$0030	$0822	MOVF 	Usart_Read_tmp_L0,W
$0031	$00A1	MOVWF 	_Usart_Read_local_result
$0032	$0008	RETURN 
$0033	$	_Usart_Write:
$0033	$	L_Usart_Write_3:
$0033	$1303	BCF	STATUS,RP1
$0034	$1283	BCF	STATUS,RP0
$0035	$01F0	CLRF 	STACK_0
$0036	$01F1	CLRF	STACK_1
$0037	$1683	BSF	STATUS,RP0
$0038	$1898	BTFSC	TXSTA,1
$0039	$0AF1	INCF	STACK_1,F
$003A	$0870	MOVF	STACK_0,W
$003B	$0271	SUBWF	STACK_1,W
$003C	$1D03	BTFSS	STATUS,Z
$003D	$2840	GOTO 	L_Usart_Write_4
$003E	$0000	nop
$003F	$2833	GOTO 	L_Usart_Write_3
$0040	$	L_Usart_Write_4:
$0040	$1283	BCF	STATUS,RP0
$0041	$0821	MOVF 	Usart_Write_argh0,W
$0042	$0099	MOVWF 	TXREG
$0043	$0008	RETURN
$0044	$	_main:
$0044	$1303	BCF	STATUS,RP1
$0045	$1683	BSF	STATUS,RP0
$0046	$0185	CLRF 	TRISA
$0047	$3015	MOVLW	21
$0048	$0099	MOVWF	SPBRG
$0049	$1518	BSF	TXSTA, BRGH
$004A	$2004	CALL	_Usart_Init
$004B	$	L_main_0:
$004B	$1303	BCF	STATUS,RP1
$004C	$1283	BCF	STATUS,RP0
$004D	$1005	BCF	PORTA,0
$004E	$201A	CALL	_Usart_Data_Ready
$004F	$01F0	CLRF 	STACK_0
$0050	$0821	MOVF	_Usart_Data_Ready_local_result,W
$0051	$0270	SUBWF	STACK_0,W
$0052	$1903	BTFSC	STATUS,Z
$0053	$286B	GOTO 	L_main_2
$0054	$2022	CALL	_Usart_Read
$0055	$0821	MOVF 	_Usart_Read_local_result,W
$0056	$00A0	MOVWF 	_i
$0057	$0820	MOVF 	_i,W
$0058	$00A1	MOVWF 	Usart_Write_argh0
$0059	$2033	CALL	_Usart_Write
$005A	$1405	BSF	PORTA,0
$005B	$3041	MOVLW	65
$005C	$00F0	MOVWF	STACK_0
$005D	$30FF	MOVLW	255
$005E	$00F1	MOVWF	STACK_1
$005F	$0BF0	DECFSZ	STACK_0,F
$0060	$2862	GOTO	$+2
$0061	$2865	GOTO	$+4
$0062	$0BF1	DECFSZ	STACK_1,F
$0063	$2862	GOTO	$-1
$0064	$285F	GOTO	$-5
$0065	$30C2	MOVLW	194
$0066	$00F2	MOVWF	STACK_2
$0067	$0BF2	DECFSZ	STACK_2,F
$0068	$2867	GOTO	$-1
$0069	$0000	NOP
$006A	$0000	NOP
$006B	$	L_main_2:
$006B	$284B	GOTO 	L_main_0
$006C	$	L_main_1:
$006C	$286C	GOTO 	$