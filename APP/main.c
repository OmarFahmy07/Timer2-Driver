/*
 * main.c
 *
 *  Created on: Sep 30, 2020
 *      Author: Omar Fahmy
 */

#include "../MCAL/Timer2/Timer2_Interface.h"
#include "../MCAL/Global Interrupt/GI_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"

#include <util/delay.h>

#define OVF_NUMBER_OF_OVERFLOWS		245
#define OVF_EARLY_COUNTS			50
#define OVF_PRELOAD_VALUE			510 - OVF_EARLY_COUNTS

#define OCM_NUMBER_OF_OVERFLOWS		310
#define OCM_EARLY_COUNTS			190
#define OCM_PRELOAD_VALUE			200 - OVF_EARLY_COUNTS
#define OCM_TOP						255

u16 counter = 0;

void ISR(void);

int main (void)
{
	Timer2_U8Init();
	DIO_U8SetPinDirection(DIO_PORTD, DIO_PIN7, DIO_PIN_OUTPUT); //OC2
	Timer2_U8EnableOVFInterrupt();
	Timer2_U8OVFSetCallBack(ISR);
	Timer2_U8Preload(OVF_PRELOAD_VALUE);
	Timer2_U8Start();
	GI_U8Enable();
	DIO_U8SetPinDirection(DIO_PORTA, DIO_PIN0, DIO_PIN_OUTPUT);


	while (1)
	{
		/*for (u8 i = 0; i < 255; i++)
		{
			Timer2_U8SetDutyCycle(i);
			_delay_ms(10);
		}

		for (u8 i = 255; i > 0; i--)
		{
			Timer2_U8SetDutyCycle(i);
			_delay_ms(10);
		}*/
	}

	return 0;
}

void ISR(void)
{
	if (counter == OVF_NUMBER_OF_OVERFLOWS)
	{
		Timer2_U8Preload(OVF_PRELOAD_VALUE);
		DIO_U8TogglePin(DIO_PORTA, DIO_PIN0);
		counter = 0;
	}
	else
	{
		counter++;
	}
}
