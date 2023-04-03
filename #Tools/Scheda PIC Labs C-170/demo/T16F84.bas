'****************************************************************
'*  File Name: T16F84                                           *
'*  Notice  : Copyright (c) 2005 EVR electronics                *
'*          : All Rights Reserved                               *
'*  Date    : 26/01/2005                                        *
'****************************************************************

    DEFINE  OSC 20

    TRISA   =   %00000000   'PORTA OUT
    TRISB   =   %00000000   'PORTB OUT
    
    TEMP    VAR BYTE
    CONTA   VAR BYTE
    
    PORTA.0 =   0
    PORTA.1 =   0
    PORTA.2 =   0
    PORTA.3 =   0

    PORTB.0 =   0
    PORTB.1 =   0
    PORTB.2 =   0
    PORTB.3 =   0
    PORTB.4 =   0                                    
    PORTB.5 =   0    
    PORTB.6 =   0                                    
    PORTB.7 =   0    

    
LOOP:
    TEMP = 1    
    for CONTA = 0 TO 3
        PORTA =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT CONTa
    PORTA.3 = 0
    pause 2000    
    TEMP = 1    
    for CONTA = 0 TO 7
        PORTB =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT conta
    PORTB.7 = 0
    pause 2000    
    Goto LOOP
