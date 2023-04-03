

/******************************\
*                              *
*           SEMAFORO           *
*                              *
*  (C) 2002 by Sergio Fiocco   *
*                              *
*      ROMA IL 09-11-2002      *
*                              *
\******************************/


#include<pic.h>
#include<delay.c>

__CONFIG(0b11001);

#define Aspetta 255

void pausa(char ripeti);

main()
{

  int i;


	TRISB = 0;

	while(1)
	{
	PORTB = 0x18;	// veicolo verde - pedone rosso
	pausa(20);

	for (i=0;i<5;i++)
	{
		PORTB =  0x1c;	// giallo
		pausa(2);
		PORTB = 0x18;	// veicolo verde - pedone rosso
		pausa(2);
	}

	PORTB = 0x22;	// veicolo rosso - pedone verde
	pausa(20);
	PORTB = 0x2;	// da qui' in poi lampeggio verde pedone
	pausa(1);
	PORTB = 0x22;
	pausa(1);
	PORTB = 0x2;
	pausa(1);
	PORTB = 0x22;
	pausa(1);
	PORTB = 0x2;
	pausa(1);
	PORTB = 0x22;
	pausa(1);
	PORTB = 0x2;
	pausa(1);
	PORTB = 0x22;
	pausa(1);
	}

}

void
pausa(char ripeti)
{
	char x;
	for(x=0;x<=ripeti;x++)
		DelayMs(Aspetta);
}
