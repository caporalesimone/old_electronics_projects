#include <stdio.h>
#include <stdlib.h>

#include "PIC16\PIC16.h"


int main(void)
{

    init_PIC16(P16F887);
    PIC_program_parse();

    printf("Fine\n");
    return 0;
}
