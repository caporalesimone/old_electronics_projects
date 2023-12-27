
_main:

;MyProject.c,1 :: 		void main() {
;MyProject.c,2 :: 		TRISA = 0;
	CLRF       TRISA+0
;MyProject.c,3 :: 		PORTA = 0xFF;
	MOVLW      255
	MOVWF      PORTA+0
;MyProject.c,4 :: 		PORTA = 0;
	CLRF       PORTA+0
;MyProject.c,5 :: 		PORTA++;
	INCF       PORTA+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      PORTA+0
;MyProject.c,6 :: 		if (PORTA > 1) {
	MOVF       PORTA+0, 0
	SUBLW      1
	BTFSC      STATUS+0, 0
	GOTO       L_main0
;MyProject.c,7 :: 		PORTA = 0;
	CLRF       PORTA+0
;MyProject.c,8 :: 		}
L_main0:
;MyProject.c,9 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
