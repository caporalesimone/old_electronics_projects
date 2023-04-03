'****************************************************************
'*  Name    : T16F676.BAS                                       *
'*  Notice  : Copyright (c) 2005 EVR electronics                *
'*          : All Rights Reserved                               *
'*  Date    : 26/01/2005                                        *
'****************************************************************

    DEFINE  OSC 20

    TRISA   =   %00000000   'PORTA OUT
    TRISC   =   %00000000   'PORTC OUT
    
    TEMP    VAR BYTE
    CONTA   VAR BYTE
    
    PORTA.0 =   0
    PORTA.1 =   0
    PORTA.2 =   0

    PORTC.0 =   0
    PORTC.1 =   0
    PORTC.2 =   0
    PORTC.3 =   0
    PORTC.4 =   0                                    
    PORTC.5 =   0    
    
LOOP:
    TEMP = 1    
    for CONTA = 0 TO 2
        PORTA =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT CONTa
    PORTA.2 = 0
    pause 2000    
    TEMP = 1    
    for CONTA = 0 TO 5
        PORTC =   TEMP
        PAUSE   2000
        TEMP = TEMP << 1
    NEXT conta
    PORTC.5 = 0
    pause 2000    
    Goto LOOP
