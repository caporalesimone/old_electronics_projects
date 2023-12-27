// PIC_Emu.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include <process.h>

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;

UINT8 ram_reg[4][0x7F]; // Ram register del PIC16F887


#define PROGRAM_SIZE 10
UINT16 programma[PROGRAM_SIZE] = {
						0x0000, // 0x0000
						0x2803, // 0x0001
						0x0000,	// 0x0002
						0x1683, // 0x0003
						0x1303, // 0x0004
						0x0185, // 0x0005
						0x30FF, // 0x0006
						0x1283, // 0x0007
						0x0085, // 0x0008
						0x2809, // 0x0009
						};

//0x0001        0x2803              GOTO       3
//0x0003        0x1683              BSF        STATUS, 5
//0x0004        0x1303              BCF        STATUS, 6
//0x0005        0x0185              CLRF       TRISA
//0x0006        0x30FF              MOVLW      255
//0x0007        0x1283              BCF        STATUS, 5
//0x0008        0x0085              MOVWF      PORTA
//0x0009        0x2809              GOTO       $+0
//

/*

Symbol List:
//** Routines locations **
//ADDRESS    SIZE    PROCEDURE
//----------------------------------------------
0x0003       [7]    _main
//** Variables locations ** 
//ADDRESS    SIZE    VARIABLE
//----------------------------------------------
0x0000       [1]    INDF
0x0003       [1]    STATUS
0x0004       [1]    FSR
0x0005       [1]    PORTA
0x000A       [1]    PCLATH
0x0020       [2]    ___DoICPAddr
0x0070       [1]    R0
0x0071       [1]    R1
0x0072       [1]    R2
0x0073       [1]    R3
0x0074       [1]    R4
0x0075       [1]    R5
0x0076       [1]    R6
0x0077       [1]    R7
0x0078       [1]    R8
0x0079       [1]    R9
0x007A       [1]    R10
0x007B       [1]    R11
0x007C       [1]    R12
0x007D       [1]    R13
0x007E       [1]    R14
0x007F       [1]    R15
0x0085       [1]    TRISA
*/








int _tmain(int argc, _TCHAR* argv[])
{
	UINT16 program_counter = 0;
	UINT16 istruzione = 0;
	UINT8 b;
	UINT8 f;
	UINT8 banksel;

	while (1) {
		istruzione = programma[program_counter];

		if (istruzione == 0) {
			program_counter++;
			continue;
		}

//0x0001        0x2803              GOTO       3
//0x0003        0x1683              BSF        STATUS, 5
//0x0004        0x1303              BCF        STATUS, 6
//0x0005        0x0185              CLRF       TRISA
//0x0006        0x30FF              MOVLW      255
//0x0007        0x1283              BCF        STATUS, 5
//0x0008        0x0085              MOVWF      PORTA
//0x0009        0x2809              GOTO       $+0

		// GOTO
		if ((istruzione & 0x2800) == 0x2800) {
			program_counter += ((istruzione & 0x7FF) - 1); // -1 perchè il vettore del programma parte da 0
			continue;
		}

		// BSF f,b (Bit b of register f is set)
		if ((istruzione & 0x1400) == 0x1400) {
			b = (istruzione & 0x380) >> 7;
			f = (istruzione & 0x7F);
			banksel = (ram_reg[0][3] & 0x60) >> 5;
			ram_reg[banksel][f] |= 1 << b;
			program_counter++;
			continue;
		}

		// BCF f,b (Bit b of register f is cleared)
		if ((istruzione & 0x1000) == 0x1000) {
			b = (istruzione & 0x380) >> 7;
			f = (istruzione & 0x7F);
			banksel = (ram_reg[0][3] & 0x60) >> 5;
			ram_reg[banksel][f] &= ~(1 << b);
			program_counter++;
			continue;
		}

		// CLRF f (The content of register f is cleared and the Z flag of the STATUS register is set)
		if ((istruzione & 0x180) == 0x180) {
			f = (istruzione & 0x7F);
			banksel = (ram_reg[0][3] & 0x60) >> 5;
			ram_reg[banksel][f] = 0;
			program_counter++;
			continue;
		}









	}

	system("PAUSE");
	return 0;
}




