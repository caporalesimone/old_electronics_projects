#ifndef __PIC16_STRUCT_h
#define __PIC16_STRUCT_h

#include <stdint.h>


enum P16_TYPE {
    P16UNDEF = 0,
    P16F887 = 1,
};


typedef struct __PIC16 {
    enum P16_TYPE pic_type;
    uint16_t ram_size;
    uint8_t  *ram;
    uint16_t flash_size;
    uint16_t *flash;

    uint8_t  w;  // Accumulator


} _PIC16;


int init_PIC16(enum P16_TYPE pic_type);
void PIC_program_parse(void);


#define RAM_BANK0   0x000
#define RAM_BANK1   0x080
#define RAM_BANK2   0x100
#define RAM_BANK3   0x180


#define PCL     0x02
#define STATUS 	0x03
#define PCLATH	0x0A



#endif // __PIC16_STRUCT_h
