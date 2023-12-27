/*
Project: SoftPWM
Ver 1.0
Author: Paolo Rognoni, 2012
MCU: Microchip PIC16F819
Clock: internal, 8MHz
Compiler: SDCC - Version 3.1.0
Linker: gputils
File: main program


This software shows how to setup a PICMicro to get a software PWM.


This software is given under license Creative Commons CC-BY-NC-ND (Italy) as describe in the following
License: Creative Commons Attribuzione - Non commerciale - Non opere derivate 3.0 Italia
http://creativecommons.org/licenses/by-nc-nd/3.0/it/legalcode
http://creativecommons.org/licenses/by-nc-nd/3.0/it/deed.it

Link:
http://www.picexperience.it
http://www.electroyou.it


*/

#include "pic16f819.h"
#include "SoftPWM.h"

// Configuration bits
int __at 0x2007  __CONFIG = _INTRC_IO&_LVP_OFF&_WDT_OFF&_MCLR_ON;

// Global variables
unsigned char uchDuty[8];
unsigned char uchStartPWM;

// Interrupt Service Routine

void Intr(void) __interrupt 0
{

// Timer 0 overflow
	if (TMR0IF) // Interrupt each 255us
	{
		PWM();		 // Call PWM() function
		TMR0IF = 0;  // Clear TMR0 interrupt bit
	}
}

void main(void)
{
	InitPic();
	uchStartPWM = 0xFF;

	uchDuty[0] = 25;  // approx. 10%
	uchDuty[1] = 50;  // approx. 20%
	uchDuty[2] = 75;  // approx. 30%
	uchDuty[3] = 100; // approx. 40%
	uchDuty[4] = 125; // approx. 50%
	uchDuty[5] = 150; // approx. 60%
	uchDuty[6] = 175; // approx. 70%
	uchDuty[7] = 200; // approx. 80%
	while (1);
}

void InitPic (void)
{

	// Oscillator setup
	OSCCON = 0x70;
	while(IOFS == 0);

	// PORTA configuration

	// Disable comparators
	ADCON1 = 0x06;

	// PORTA configured as input
	TRISA = 0xFF;

	// PORTB configured as output
	TRISB = 0x00;

	PORTB = 0x00;

	// TMR0 setup
	OPTION_REG = 0x80;

	// TMR2 setup
	T2CON = 0x07;
	TMR2ON = 1;

	// TMR0 and General interrupt enable
	TMR0IE = 1;
	PEIE = 1;
	GIE = 1;

	uchStartPWM = 0;
	uchDuty[0] = 0;
	uchDuty[1] = 0;
	uchDuty[2] = 0;
	uchDuty[3] = 0;
	uchDuty[4] = 0;
	uchDuty[5] = 0;
	uchDuty[6] = 0;
	uchDuty[7] = 0;

}



// Software PWM made with the comparison between a duty value and Timer2 value

void PWM (void)
{
	if (uchStartPWM & 1 == 1)
	{
		if (uchDuty[0] >= TMR2)
		{
			RB0 = 1;
		} else {
			RB0 = 0;
		}
	}

	if (uchStartPWM & 2 == 0x02)
	{
		if (uchDuty[1] >= TMR2)
		{
			RB1 = 1;
		} else {
			RB1 = 0;
		}
	}

	if (uchStartPWM & 4 == 0x04)
	{
		if (uchDuty[2] >= TMR2)
		{
			RB2 = 1;
		} else {
			RB2 = 0;
		}
	}

	if (uchStartPWM & 0x08 == 8)
	{
		if (uchDuty[3] >= TMR2)
		{
			RB3 = 1;
		} else {
			RB3 = 0;
		}
	}

	if (uchStartPWM & 0x10== 0x10)
	{
		if (uchDuty[4] >= TMR2)
		{
			RB4 = 1;
		} else {
			RB4 = 0;
		}
	}

	if (uchStartPWM & 0x20 == 0x20)
	{
		if (uchDuty[5] >= TMR2)
		{
			RB5 = 1;
		} else {
			RB5 = 0;
		}
	}

	if (uchStartPWM & 0x40 == 0x40)
	{
		if (uchDuty[6] >= TMR2)
		{
			RB6 = 1;
		} else {
			RB6 = 0;
		}
	}

	if (uchStartPWM & 0x80 == 0x80)
	{
		if (uchDuty[7] >= TMR2)
		{
			RB7 = 1;
		} else {
			RB7 = 0;
		}
	}

}

