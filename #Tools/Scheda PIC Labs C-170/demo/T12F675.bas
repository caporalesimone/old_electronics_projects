'****************************************************************
'*  Name    : T12F675.BAS                                       *
'*  Notice  : Copyright (c) 2005 EVR electronics                *
'*          : All Rights Reserved                               *
'*  Date    : 26/01/2005                                        *
'****************************************************************

    TRISIO  =   0      'All output
    
    ANSEL   =   0
    ADCON0  =   0

    GPIO.0  =   0
    GPIO.1  =   0
    GPIO.2  =   0
    GPIO.4  =   0
    GPIO.5  =   0
    
LOOP:
    
    GPIO.0  =   1
    PAUSE   2000
    GPIO.0  =   0
    PAUSE   2000
    GPIO.1  =   1
    PAUSE   2000
    GPIO.1  =   0
    PAUSE   2000
    GPIO.2  =   1
    PAUSE   2000
    GPIO.2  =   0
    PAUSE   2000
    GPIO.4  =   1
    PAUSE   2000
    GPIO.4  =   0
    PAUSE   2000
    GPIO.5  =   1
    PAUSE   2000
    GPIO.5  =   0
    PAUSE   2000
    
    GOTO    LOOP
    
