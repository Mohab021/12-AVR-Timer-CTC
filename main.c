
#include <avr/io.h>
#define F_CPU 4000000UL
#include "AVR_Ports.h"
#include "AVR_GPIO_Declarations.h"
#include "AVR_Counter_Timer.h"

int main(void)
{
	Pin_Direction(B, 3, output); //OC0 output pin
	Pin_Reset(B, 3);

	uint8_t Low_Comp_Valu = 64;
	uint8_t High_Comp_Valu = 128;
	uint8_t Comp_Valu = 128;

	while(1)
	{
		Waveform_Gen_NM(Comp_Valu); //Generate Square wave Using Normal mode
		//Waveform_Gen_CTC_FP(Comp_Valu); //Generate Square wave Using CTC mode - Fixed Pulses
		//Waveform_Gen_CTC_DP(Low_Comp_Valu, High_Comp_Valu); //Generate Square wave Using CTC mode - Different Pulses
	}
}
