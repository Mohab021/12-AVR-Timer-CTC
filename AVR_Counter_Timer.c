
#include <avr/io.h>
#define F_CPU 4000000UL
#include "AVR_Counter_Timer.h"

void Waveform_Gen_NM(uint8_t Comp_Value)
{
	/*
	Square wave using Normal Mode
	The generated waveform has a fixed frequency that is dependent on Fosc
	Fosc = 4MHz waveform, T = 0.25 ?s
	Time period of square wave: 2 x 256 x 0.25 ?s = 128 ?s
	Frequency of wave= 1/128 ?s = 7812.5 Hz
	*/
	
	TCCR0 = 0x11; //0b00010001, Normal mode, no pre-scaling, Toggle on compare match
	OCR0 = Comp_Value; //Compare value equal to 50% of 0XFF (256 cycles)
}

void Waveform_Gen_CTC_FP(uint8_t Comp_Value)
{
	/*
	Square wave using CTC Mode - Fixed Pulses
	The generated waveform's frequency can be adjusted because it's dependent on OCR0 value
	Fosc = 4MHz waveform, T = 0.25 ?s
	Time period of square wave: 2 x (1 + OCR0) x 0.25 ?s
	= 2 x 129 x 0.25 ?s = 64.5 ?s (E.g. using OCR0 = 128)
	Frequency of wave= 1/64.5 ?s = 15503.876 Hz
	*/
	
	TCCR0 = 0x19; //0b00011001, CTC mode, no pre-scaling, Toggle on compare match
	OCR0 = Comp_Value; //Compare value equal to 50% of 0XFF (256 cycles)
}

void Waveform_Gen_CTC_DP(uint8_t LP_Comp_Value, uint8_t HP_Comp_Value)
{
	/*
	Square wave using CTC Mode - Different Pulses
	The generated waveform's frequency can be adjusted because it's dependent on OCR0 value
	*/
	
	OCR0 = LP_Comp_Value; //Low Compare value to Set
	TCCR0 = 0x39; //0b00111001, CTC mode, no pre-scaling, Set on compare match
	while ( !(TIFR & (1<<OCF0)) ) ; //Wait until OCF0 is set
	TIFR = (1<<OCF0); //Clear OCF0 by writing [1] to it (make it zero again)
	
	OCR0 = HP_Comp_Value; //High Compare value to Reset
	TCCR0 = 0x29; //0b00101001, CTC mode, no pre-scaling, Reset on compare match
	while ( !(TIFR & (1<<OCF0)) ) ; //Wait until OCF0 is set
	TIFR = (1<<OCF0); //Clear OCF0 by writing [1] to it (make it zero again)
}
