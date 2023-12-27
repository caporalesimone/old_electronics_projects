#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // getch()

#include "PIC16.h"


char register_string_general_purpose[5];
char register_string_bank0[][15] = {
    "-\0",
    "TMR0\0",
    "PCL\0",
    "STATUS\0",
    "FSR\0",
    "PORTA\0",
    "PORTB\0",
    "PORTC\0",
    "-\0",
    "PORTE\0",
    "PCLATH\0",
    "INTCON\0",
    "PIR1\0",
    "PIR2\0",
    "TMR1L\0",
    "TMR1H\0",
    "T1CON\0",
    "TMR2\0",
    "T2CON\0",
    "SSPBUF\0",
    "SSPCON\0",
    "CCPR1L\0",
    "CCPR1H\0",
    "CCP1CON\0",
    "RCSTA\0",
    "TXREG\0",
    "RCREG\0",
    "CCPR2L\0",
    "CCPR2H\0",
    "CCP2CON\0",
    "ADRESH\0",
    "ADCON0\0"
    };

char register_string_bank1[][15] = {
    "-\0",
    "OPTION_REG\0",
    "PCL\0",
    "STATUS\0",
    "FSR\0",
    "TRISA\0",
    "\0",
    "\0","\0","\0","\0"

    };

char register_string_bank2[][15] = {""};
char register_string_bank3[][15] = {""};


static const char print_assembly = 1;
_PIC16 pic_micro;



void P16_decode_opcode(uint16_t opcode);
char* register_name(uint16_t reg_address);


int init_PIC16(enum P16_TYPE pic_type) {

    switch (pic_type) {
        case P16F887:
            pic_micro.pic_type = pic_type;
            pic_micro.ram_size = 512;
            pic_micro.flash_size = (8192 / 2);
            break;

        case P16UNDEF:
        default:
            return 1;
    }

    pic_micro.ram = calloc( pic_micro.ram_size, sizeof(uint8_t) );
    pic_micro.flash = calloc( pic_micro.flash_size, sizeof(uint16_t) );
    return 0;
}


void PIC_program_parse(void) {

//#define PROGRAM_SIZE 10
//uint16_t programma[PROGRAM_SIZE] = {
//  0x0000, // 0x0000
//  0x2803, // 0x0001
//  0x0000,	// 0x0002
//  0x1683, // 0x0003
//  0x1303, // 0x0004
//  0x0185, // 0x0005
//  0x30FF, // 0x0006
//  0x1283, // 0x0007
//  0x0085, // 0x0008
//  0x2809, // 0x0009
//};

//0x0001        0x2803              GOTO       3
//0x0003        0x1683              BSF        STATUS, 5
//0x0004        0x1303              BCF        STATUS, 6
//0x0005        0x0185              CLRF       TRISA
//0x0006        0x30FF              MOVLW      255
//0x0007        0x1283              BCF        STATUS, 5
//0x0008        0x0085              MOVWF      PORTA
//0x0009        0x2809              GOTO       $+0

#define PROGRAM_SIZE 20
uint16_t programma[PROGRAM_SIZE] = {
0x0000,
0x2803, 0x0000, 0x1683, 0x1303, 0x0185,
0x30FF, 0x1283, 0x0085, 0x0185, 0x0A05,
0x00F0, 0x0870, 0x0085, 0x0805, 0x3C01,
0x1803, 0x2813, 0x0185, 0x2813,
};

//void main() {
//     TRISA = 0;
//     PORTA = 0xFF;
//     PORTA = 0;
//     PORTA++;
//     if (PORTA > 1) {
//        PORTA = 0;
//     }
//}
//;Address Opcode 	ASM
//0x0000	0x2803      	GOTO       3
//_main:
//;MyProject.c,1 :: 		void main() {
//;MyProject.c,2 :: 		TRISA = 0;
//0x0003	0x1683      	BSF        STATUS, 5
//0x0004	0x1303      	BCF        STATUS, 6
//0x0005	0x0185      	CLRF       TRISA
//;MyProject.c,3 :: 		PORTA = 0xFF;
//0x0006	0x30FF      	MOVLW      255
//0x0007	0x1283      	BCF        STATUS, 5
//0x0008	0x0085      	MOVWF      PORTA
//;MyProject.c,4 :: 		PORTA = 0;
//0x0009	0x0185      	CLRF       PORTA
//;MyProject.c,5 :: 		PORTA++;
//0x000A	0x0A05      	INCF       PORTA, 0
//0x000B	0x00F0      	MOVWF      R0
//0x000C	0x0870      	MOVF       R0, 0
//0x000D	0x0085      	MOVWF      PORTA
//;MyProject.c,6 :: 		if (PORTA > 1) {
//0x000E	0x0805      	MOVF       PORTA, 0
//0x000F	0x3C01      	SUBLW      1
//0x0010	0x1803      	BTFSC      STATUS, 0
//0x0011	0x2813      	GOTO       L_main0
//;MyProject.c,7 :: 		PORTA = 0;
//0x0012	0x0185      	CLRF       PORTA
//;MyProject.c,8 :: 		}
//L_main0:
//;MyProject.c,9 :: 		}
//L_end_main:
//0x0013	0x2813      	GOTO       $+0
//
//
//

    char ch;
    uint16_t program_counter = 0;
    uint16_t opcode = 0;

    memset(pic_micro.ram, 0, pic_micro.ram_size);
    memset(pic_micro.flash, 0x3FFF, pic_micro.flash_size); // Attenzione fa tutto a FF in realtà
    memcpy(pic_micro.flash, programma, sizeof(uint16_t) * PROGRAM_SIZE );

    pic_micro.ram[PCL] = 1; // Inizializzo il PC alla prima locazione

    while(1) {

        program_counter = pic_micro.ram[PCL];
        opcode = (uint16_t)pic_micro.flash[program_counter];
        P16_decode_opcode(opcode);
        ch = getch();
        if (ch != 0x20)
            break;

    }

}


void P16_decode_opcode(uint16_t opcode) {

    uint8_t bank = (pic_micro.ram[RAM_BANK0 | STATUS] & 0x0060) << 2; // << 2 perchè in questo modo facendo l'OR con l'indirizzo del registro accedo alla posizione assoluta nel vettore della ram.
    uint16_t k;
    uint16_t f;
    uint16_t b;
    uint16_t d;

    uint8_t temp;

	switch(opcode & 0x3000)
	{
	case 0x0000:
		switch(opcode & 0x0F00) {
		case 0x0000:
			switch(opcode & 0x0080) {
			case 0x0000:
                switch(opcode & 0x007F) {
                case 0x0000:
                case 0x0020:
                case 0x0040:
                case 0x0060:
                    // NOP     --  	No Operation                 1     0000000 xx00000
                    if (print_assembly) printf("$%#05x - NOP\n", pic_micro.ram[PCL]);
                    pic_micro.ram[PCL]++;
                    break;
                case 0x0008:
                    // RETURN  --  	Return from Subroutine       2     0000000 0001000
                    break;
                case 0x0009:
                    //RETFIE  --  	Return from interrupt        2     0000000 0001001
                    break;
                case 0x0063:
                    // SLEEP   --  	Go into Standby mode         1     0000000 1100011   	TO,PD
                    break;
                case 0x0064:
                    // CLRWDT  --  	Clear Watchdog Timer         1     0000000 1100100   	TO,PD
                    break;
                };
                break;
            case 0x0080:
                // MOVWF   f  	Move W to f                  1     0000001 fffffff
                // 0 <= f <= 127
                // (W) -> f
                f = (opcode & 0x007F);
   				// if (print_assembly) printf("%#05x - MOVWF %#04x\n", pic_micro.ram[PCL], f);
   				if (print_assembly) printf("$%#05x - MOVWF %s\n", pic_micro.ram[PCL], register_name(bank | f));
				pic_micro.ram[ bank | f ] = pic_micro.w;
                pic_micro.ram[PCL]++;
                break;
            };
            break;

		case 0x0100:
			switch(opcode & 0x0080) {
			case 0x0000:
				// CLRW    --  	Clear W                      1     0000010 xxxxxxx 	Z
                // 00h -> W
                // 1 -> Z
				if (print_assembly) printf("$%#05x - CLRW\n", pic_micro.ram[PCL]);
				pic_micro.w = 0;
				pic_micro.ram[RAM_BANK0 | STATUS] = pic_micro.ram[STATUS] | (1 << 2);
				pic_micro.ram[RAM_BANK1 | STATUS] = pic_micro.ram[STATUS] | (1 << 2);
				pic_micro.ram[RAM_BANK2 | STATUS] = pic_micro.ram[STATUS] | (1 << 2);
				pic_micro.ram[RAM_BANK3 | STATUS] = pic_micro.ram[STATUS] | (1 << 2);
				pic_micro.ram[PCL]++;
				break;
			case 0x0080:
				// CLRF    f  	Clear f                      1     0000011 fffffff 	Z       2
                // 0 <= f <= 127
                // 00h -> f
                // 1 -> Z
                f = (opcode & 0x007F);
				// if (print_assembly) printf("%#05x - CLRF  %#04x\n", pic_micro.ram[PCL], f);
				if (print_assembly) printf("$%#05x - CLRF  %s\n", pic_micro.ram[PCL], register_name(bank | f));
				pic_micro.ram[bank | f] = 0;
				pic_micro.ram[PCL]++;
				break;
			};
			break;
        case 0x0200:
		case 0x0300:
		case 0x0400:
		case 0x0500:
		case 0x0600:
		case 0x0700:
		    break;
		case 0x0800:
            // MOVF    f, d 	Move f                       1     001000 dfffffff 	Z       1, 2
            // 0 <= f <= 127
            // d in [0,1]
            // (f) -> destination
            // Status Affected: Z
            // The contents of register ’f’ is moved to a destination dependent upon the status of ’d’. If ’d’ = 0, destination is W register. If ’d’ = 1, the destination is
            // file register ’f’ itself. ’d’ = 1 is useful to test a file register since status flag Z is affected.
            f = (opcode & 0x007F);
            d = ((opcode & 0x0080) >> 7);
			if (print_assembly) printf("$%#05x - MOVF  %s, %d\n", pic_micro.ram[PCL], register_name(bank | f), d);

			if( (opcode & 0x0080) == 0 ) {
				pic_micro.w = pic_micro.ram[bank | f];
				if (pic_micro.w == 0)
					pic_micro.ram[bank | STATUS] |= 0x04;
				else
					pic_micro.ram[bank | STATUS] &= ~0x04;
			}
			else {
				if (pic_micro.ram [bank | f ] == 0)
					pic_micro.ram[bank | STATUS] |= 0x04;
				else
					pic_micro.ram[bank | STATUS] &= ~0x04;
			};
			pic_micro.ram[PCL]++;

			break;
		case 0x0900:
		    break;
		case 0x0A00:
			// INCF    f, d 	Increment f                  1     001010 dfffffff	Z       1, 2
			// 0 <= f <= 127
            // d in [0,1]
            // The contents of register 'f' are incremented. If 'd' is 0 the result is placed in the W register. If 'd' is 1 the result is placed back in register 'f'.
            f = (opcode & 0x007F);
            d = ((opcode & 0x0080) >> 7);
			if (print_assembly) printf("$%#05x - INCF  %s, %d\n", pic_micro.ram[PCL], register_name(bank | f) ,d);
			if( d == 0 ) {
                pic_micro.w = pic_micro.ram[bank | f] + 1;
				if (pic_micro.w == 0)
                    pic_micro.ram[bank | STATUS] |= 0x04;
				else
					pic_micro.ram[bank | STATUS] &= ~0x04;
			}
			else {
			    pic_micro.ram[bank | f]++;
				if (pic_micro.ram[bank | f] == 0)
					pic_micro.ram[bank | STATUS] |= 0x04;
				else
					pic_micro.ram[bank | STATUS] &= ~0x04;
			};
			pic_micro.ram[PCL]++;
			break;
		case 0x0B00:
		case 0x0C00:
		case 0x0D00:
		case 0x0E00:
		case 0x0F00:
            break;
		}
		break;

	case 0x1000:
		switch(opcode & 0x0C00) {
		case 0x0000:
			// BCF f,b
			// 0 <= f <= 127 ; 0 <= b <= 7
			// 0 -> f<b>
			f = (opcode & 0x007F);
			b = ((opcode & 0x0380) >> 7);
			if (print_assembly) printf("$%#05x - BCF   %s, %d\n", pic_micro.ram[PCL], register_name(bank | f) ,b);
			pic_micro.ram[bank | f] &= ~(0x01 << b);
			pic_micro.ram[PCL]++;
			break;
		case 0x0400:
			// BSF f,b
			// 0 <= f <= 127 ; 0 <= b <= 7
			// 1 -> f<b>
			f = (opcode & 0x007F);
			b = ((opcode & 0x0380) >> 7);
            if (print_assembly) printf("$%#05x - BSF   %s, %d\n", pic_micro.ram[PCL], register_name(bank | f), b);
			pic_micro.ram[bank | f] |= (0x01 << b);
			pic_micro.ram[PCL]++;
			break;
		case 0x0800:
			// BTFSC   f, b 	Bit Test f, Skip if Clear    1(2)  0110 bbbfffffff           3
            // 0 <= f <= 127
            // 0 <= b <= 7
            // skip if (f<b>) = 0
            // Description: If bit 'b' in register 'f' is '0' then the next instruction is skipped. If bit 'b' is '0' then the
            // next instruction (fetched during the current instruction execution) is discarded, and a NOP is executed instead,
            // making this a 2 cycle instruction.
			f = (opcode & 0x007F);
			b = ((opcode & 0x0380) >> 7);
			if (print_assembly) printf("$%#05x - BTFSC %s, %d\n", pic_micro.ram[PCL], register_name(bank | f), b);
			if((pic_micro.ram[bank | f] & (0x01 << b)) == 0) {
				pic_micro.ram[PCL]++;
			}
			pic_micro.ram[PCL]++;
			break;
		case 0x0C00:
			break;
		}
		break;

	case 0x2000:
		switch(opcode & 0x0800){
		case 0x0000: // CALL
			break;
		case 0x0800:
			// GOTO k
			// 0 <= k <= 2047
			// k -> PC<10:0> - PCLATH<4:3> -> PC<12:11>
			k = (opcode & 0x07FF);
			if (print_assembly) printf("$%#05x - GOTO  %#05x\n", pic_micro.ram[PCL], k);
			pic_micro.ram[PCL] = k | ((pic_micro.ram[PCLATH] & 0x18) << 8);
			break;
		}
		break;

	case 0x3000:
		switch(opcode & 0x0F00){
            case 0x0000:
            case 0x0100:
            case 0x0200:
            case 0x0300:
                // MOVLW   k  	Move literal to W            1     1100xx kkkkkkkk
                // 0 <= k <= 255
                // k -> W
                k = (opcode & 0x00FF);
                if (print_assembly) printf("$%#05x - MOVLW %#04x\n", pic_micro.ram[PCL], k);
                pic_micro.w = k;
                pic_micro.ram[PCL]++;
                break;

            case 0x0400:
            case 0x0500:
            case 0x0600:
            case 0x0700:
                //RETLW   k  	Return with literal in W     2     1101xx kkkkkkkk
            case 0x0800:
                //IORLW   k  	Inclusive OR literal with W  1     111000 kkkkkkkk   	Z
            case 0x0900:
                //ANDLW   k 	AND literal with W           1     111001 kkkkkkkk   	Z
            case 0x0A00:
                //XORLW   k  	Exclusive OR literal with W  1     111010 kkkkkkkk   	Z
            case 0x0C00:
            case 0x0D00:
                // SUBLW   k  	Subtract W from literal      1     11110x kkkkkkkk   	C,DC,Z
                // 0 <= k <= 255
                // k - (W) -> W
                // Status Affected: C, DC, Z
                k = (opcode & 0x00FF);
                if (print_assembly) printf("$%#05x - SUBLW %#04x\n", pic_micro.ram[PCL], k);

                if((0xF0 & ((0x0F &(~pic_micro.w)) + 1 + (opcode & 0x000F))) !=0)
                    pic_micro.ram[bank | STATUS] |= 0x02;
                else
                    pic_micro.ram[bank | STATUS] &=~ 0x02;

                temp = (~pic_micro.w + 1) + k;
                pic_micro.w = (unsigned char)(0x00FF &temp);

                if ( (0xFF00 & temp) != 0)
                    pic_micro.ram[bank | STATUS] &= ~0x01;
                else
                    pic_micro.ram[bank | STATUS] |= 0x01;

                if (pic_micro.w == 0)
                    pic_micro.ram[bank | STATUS] |= 0x04;
                else
                    pic_micro.ram[bank | STATUS] &= ~0x04;

                pic_micro.ram[PCL]++;
                break;
            case 0x0E00:
            case 0x0F00:
                //ADDLW   k  	Add literal and W            1     11111x kkkkkkkk   	C,DC,Z
                break;


            };
            break;

	}


    // Clonare STATUS e gli altri registri duplicati !!!
    temp = pic_micro.ram[bank | STATUS];
    pic_micro.ram[RAM_BANK0 | STATUS] = temp;
	pic_micro.ram[RAM_BANK1 | STATUS] = temp;
	pic_micro.ram[RAM_BANK2 | STATUS] = temp;
	pic_micro.ram[RAM_BANK3 | STATUS] = temp;

}


char* register_name(uint16_t reg_address) {

    char num_str[5];
    char *retval = register_string_bank0[0];
    uint8_t bank = ((reg_address >> 2) & 0x0060) >> 5;
    uint8_t address = (reg_address & 0xFF);

    itoa(address,num_str,16);
    sprintf(register_string_general_purpose,"0x%s",num_str);
    retval = register_string_general_purpose;

    switch (bank) {
        case 0:
            if (address < (RAM_BANK0 + 20)) {
                retval = register_string_bank0[address];
            }
            break;
        case 1:
            if (address < (RAM_BANK1 + 0x86)) {
                address -= 0x80;
                retval = register_string_bank1[address];
            }
            break;
        case 2:
            if (address < (RAM_BANK2 + 0x00)) {
                address -= 0x100;
                retval = register_string_bank2[address];
            }
            break;
        case 3:
            if (address < (RAM_BANK3 + 0x00)) {
                address -= 0x180;
                retval = register_string_bank3[address];
            }
            break;
    };

    return retval;

}


