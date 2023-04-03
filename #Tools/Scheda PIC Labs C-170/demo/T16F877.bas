'****************************************************************
'*  File Name: T16F877                                           *
'*  Notice  : Copyright (c) 2005 EVR electronics                *
'*          : All Rights Reserved                               *
'*  Date    : 26/01/2005                                        *
'****************************************************************

    DEFINE  OSC 20

    TRISA   =   %00000000   'PORTA OUT
    TRISB   =   %00000000   'PORTB OUT
    TRISC   =   %00000000   'PORTC OUT
    TRISD   =   %00000000   'PORTD OUT
    TRISE   =   %00000000   'PORTE OUT
    
    TEMP    VAR BYTE
    CONTA   VAR BYTE
    
    PORTA.0 =   0
    PORTA.1 =   0
    PORTA.2 =   0
    PORTA.3 =   0
    PORTA.5 =   0

    PORTB.0 =   0
    PORTB.1 =   0
    PORTB.2 =   0
    PORTB.3 =   0
    PORTB.4 =   0                                    
    PORTB.5 =   0    
    PORTB.6 =   0                                    
    PORTB.7 =   0    

    PORTC.0 =   0
    PORTC.1 =   0
    PORTC.2 =   0
    PORTC.3 =   0
    PORTC.4 =   0                                    
    PORTC.5 =   0    
    PORTC.6 =   0                                    
    PORTC.7 =   0    

    PORTD.0 =   0
    PORTD.1 =   0
    PORTD.2 =   0
    PORTD.3 =   0
    PORTD.4 =   0                                    
    PORTD.5 =   0    
    PORTD.6 =   0                                    
    PORTD.7 =   0    

    PORTE.0 =   0
    PORTE.1 =   0
    PORTE.2 =   0

    
LOOP:
    TEMP = 1    
    for CONTA = 0 TO 3
        PORTA =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT CONTa
    PORTA.3 = 0
    PORTA.5 = 1
    PAUSE 2000
    PORTA.5 = 0
    PAUSE 2000
    
    TEMP = 1    
    for CONTA = 0 TO 7
        PORTB =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT conta
    PORTB.7 = 0
    pause 2000    
    
    TEMP = 1    
    for CONTA = 0 TO 7
        PORTC =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT conta
    PORTC.7 = 0
    pause 2000    

    TEMP = 1    
    for CONTA = 0 TO 7
        PORTD =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT conta
    PORTD.7 = 0
    pause 2000    

    TEMP = 1    
    for CONTA = 0 TO 2
        PORTE =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT conta
    PORTE.2 = 0
    pause 2000    
    
    Goto LOOP
