/*
 * Timer2_Program.c
 *
 *  Created on: Sep 30, 2020
 *      Author: Omar Fahmy
 */

/* LIB LAYER */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/STD_TYPES.h"
/* MCAL LAYER */
#include "Timer2_Configure.h"
#include "Timer2_Private.h"

/* Global Pointers to Functions for Calling Back */
void (*GLOB_VidTimer2OVFPtrCallBack) (void) = NULL;
void (*GLOB_VidTimer2OCMPtrCallBack) (void) = NULL;

/************************************************************************************/
/*						PUBLIC FUNCTIONS IMPLEMENTATION								*/
/************************************************************************************/

u8 Timer2_U8Init(void)
{
#if MODE == NORMAL
	CLR_BIT(TCCR2_REGISTER, WGM21);
	CLR_BIT(TCCR2_REGISTER, WGM20);
#if OC2_NON_PWM == DISCONNECT_OC2
	CLR_BIT(TCCR2_REGISTER, COM21);
	CLR_BIT(TCCR2_REGISTER, COM20);
#elif OC2_NON_PWM == TOGGLE_OC2
	CLR_BIT(TCCR2_REGISTER, COM21);
	SET_BIT(TCCR2_REGISTER, COM20);
#elif OC2_NON_PWM == CLEAR_OC2
	SET_BIT(TCCR2_REGISTER, COM21);
	CLR_BIT(TCCR2_REGISTER, COM20);
#elif OC2_NON_PWM == SET_OC2
	SET_BIT(TCCR2_REGISTER, COM21);
	SET_BIT(TCCR2_REGISTER, COM20);
#else
#error "Incorrect output compare pin (OC2) behaviour in case of normal mode"
#endif
#elif MODE == PHASE_CORRECT
	CLR_BIT(TCCR2_REGISTER, WGM21);
	SET_BIT(TCCR2_REGISTER, WGM20);
	/* For ensuring compatibility with future devices */
	CLR_BIT(TCCR2_REGISTER, FOC2);
#if OC2_PHASE_CORRECT == DISCONNECT_OC2
	CLR_BIT(TCCR2_REGISTER, COM21);
	CLR_BIT(TCCR2_REGISTER, COM20);
#elif OC2_PHASE_CORRECT == NON_INVERTING_OC2
	SET_BIT(TCCR2_REGISTER, COM21);
	CLR_BIT(TCCR2_REGISTER, COM20);
#elif OC2_PHASE_CORRECT == INVERTING_OC2
	SET_BIT(TCCR2_REGISTER, COM21);
	SET_BIT(TCCR2_REGISTER, COM20);
#else
#error "Incorrect output compare pin (OC2) behavior in case of phase correct mode"
#endif
#elif MODE == CTC
	SET_BIT(TCCR2_REGISTER, WGM21);
	CLR_BIT(TCCR2_REGISTER, WGM20);
#if OC2_NON_PWM == DISCONNECT_OC2
	CLR_BIT(TCCR2_REGISTER, COM21);
	CLR_BIT(TCCR2_REGISTER, COM20);
#elif OC2_NON_PWM == TOGGLE_OC2
	CLR_BIT(TCCR2_REGISTER, COM21);
	SET_BIT(TCCR2_REGISTER, COM20);
#elif OC2_NON_PWM == CLEAR_OC2
	SET_BIT(TCCR2_REGISTER, COM21);
	CLR_BIT(TCCR2_REGISTER, COM20);
#elif OC2_NON_PWM == SET_OC2
	SET_BIT(TCCR2_REGISTER, COM21);
	SET_BIT(TCCR2_REGISTER, COM20);
#else
#error "Incorrect output compare pin (OC2) behaviour in case of CTC mode"
#endif
#elif MODE == FAST_PWM
	SET_BIT(TCCR2_REGISTER, WGM21);
	SET_BIT(TCCR2_REGISTER, WGM20);
	/* For ensuring compatibility with future devices */
	CLR_BIT(TCCR2_REGISTER, FOC2);
#if OC2_FAST_PWM == DISCONNECT_OC2
	CLR_BIT(TCCR2_REGISTER, COM21);
	CLR_BIT(TCCR2_REGISTER, COM20);
#elif OC2_FAST_PWM == NON_INVERTING_OC2
	SET_BIT(TCCR2_REGISTER, COM21);
	CLR_BIT(TCCR2_REGISTER, COM20);
#elif OC2_FAST_PWM == INVERTING_OC2
	SET_BIT(TCCR2_REGISTER, COM21);
	SET_BIT(TCCR2_REGISTER, COM20);
#else
#error "Incorrect output compare pin (OC2) behaviour in case of fast PWM mode"
#endif
#else
#error "Incorrect timer0 mode"
#endif
#if CLOCK_SELECT == NO_CLOCK_SOURCE
	CLR_BIT(TCCR2_REGISTER, CS22);
	CLR_BIT(TCCR2_REGISTER, CS21);
	CLR_BIT(TCCR2_REGISTER, CS20);
#elif CLOCK_SELECT == NO_PRESCALER
	CLR_BIT(TCCR2_REGISTER, CS22);
	CLR_BIT(TCCR2_REGISTER, CS21);
	SET_BIT(TCCR2_REGISTER, CS20);
#elif CLOCK_SELECT == PRESCALER_8
	CLR_BIT(TCCR2_REGISTER, CS22);
	SET_BIT(TCCR2_REGISTER, CS21);
	CLR_BIT(TCCR2_REGISTER, CS20);
#elif CLOCK_SELECT == PRESCALER_32
	CLR_BIT(TCCR2_REGISTER, CS22);
	SET_BIT(TCCR2_REGISTER, CS21);
	SET_BIT(TCCR2_REGISTER, CS20);
#elif CLOCK_SELECT == PRESCALER_64
	SET_BIT(TCCR2_REGISTER, CS22);
	CLR_BIT(TCCR2_REGISTER, CS21);
	CLR_BIT(TCCR2_REGISTER, CS20);
#elif CLOCK_SELECT == PRESCALER_128
	SET_BIT(TCCR2_REGISTER, CS22);
	CLR_BIT(TCCR2_REGISTER, CS21);
	SET_BIT(TCCR2_REGISTER, CS20);
#elif CLOCK_SELECT == PRESCALER_256
	SET_BIT(TCCR2_REGISTER, CS22);
	SET_BIT(TCCR2_REGISTER, CS21);
	CLR_BIT(TCCR2_REGISTER, CS20);
#elif CLOCK_SELECT == PRESCALER_1024
	SET_BIT(TCCR2_REGISTER, CS22);
	SET_BIT(TCCR2_REGISTER, CS21);
	SET_BIT(TCCR2_REGISTER, CS20);
#elif CLOCK_SELECT == ASYNCHRONOUS_TOSC1
	SET_BIT(ASSR_REGISTER, AS2);
#else
#error "Incorrect clock selection"
#endif
	return NO_ERROR;
}

u8 Timer2_U8Preload(const u8 LOC_U8Value)
{
	TCNT2_REGISTER = LOC_U8Value;
	return NO_ERROR;
}

u8 Timer2_U8SetCTCValue(const u8 LOC_U8Value)
{
	OCR2_REGISTER = LOC_U8Value;
	return NO_ERROR;
}

u8 Timer2_U8GetCounterValue(u8* const LOC_U8Value)
{
	if (LOC_U8Value != NULL)
	{
		*LOC_U8Value = TCNT2_REGISTER;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer2_U8CheckTCNT2BusyFlag(u8* const LOC_U8Value)
{
	if (LOC_U8Value != NULL)
	{
		*LOC_U8Value = GET_BIT(ASSR_REGISTER, TCN2UB);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer2_U8CheckOCR2BusyFlag(u8* const LOC_U8Value)
{
	if (LOC_U8Value != NULL)
	{
		*LOC_U8Value = GET_BIT(ASSR_REGISTER, OCR2UB);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer2_U8CheckTCCR2BusyFlag(u8* const LOC_U8Value)
{
	if (LOC_U8Value != NULL)
	{
		*LOC_U8Value = GET_BIT(ASSR_REGISTER, TCR2UB);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer2_U8EnableOVFInterrupt(void)
{
	SET_BIT(TIMSK_REGISTER, TOIE2);
	return NO_ERROR;
}

u8 Timer2_U8DisableOVFInterrupt(void)
{
	CLR_BIT(TIMSK_REGISTER, TOIE2);
	return NO_ERROR;
}

u8 Timer2_U8EnableOCMInterrupt(void)
{
	SET_BIT(TIMSK_REGISTER, OCIE2);
	return NO_ERROR;
}

u8 Timer2_U8DisableOCMInterrupt(void)
{
	CLR_BIT(TIMSK_REGISTER, OCIE2);
	return NO_ERROR;
}

u8 Timer2_U8OVFSetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidTimer2OVFPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer2_U8OCMSetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidTimer2OCMPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer2_U8OVFPollingOnFlag(void)
{
	/* Wait until flag is fired */
	while ( !GET_BIT(TIFR_REGISTER, TOV2) );
	/* Clear flag */
	SET_BIT(TIFR_REGISTER, TOV2);
	return NO_ERROR;
}

u8 Timer2_U8OCMPollingOnFlag(void)
{
	/* Wait until flag is fired */
	while ( !GET_BIT(TIFR_REGISTER, OCF2) );
	/* Clear flag */
	SET_BIT(TIFR_REGISTER, OCF2);
	return NO_ERROR;
}

u8 Timer2_U8SetDutyCycle(const f32 LOC_F32DutyCycle)
{
	if (LOC_F32DutyCycle >= MINIMUM_DUTYCYCLE && LOC_F32DutyCycle <= MAXIMUM_DUTYCYCLE)
	{
		Timer2_U8SetCTCValue( ( LOC_F32DutyCycle / 100 ) * ( RESOLUTION - 1 ) );
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 Timer2_U8ResetPrescaler(void)
{
	SET_BIT(SFIOR_REGISTER, PSR2);
	return NO_ERROR;
}

/************************************************************************************/
/*						PRIVATE FUNCTIONS IMPLEMENTATION							*/
/************************************************************************************/

void __vector_4(void)
{
	if (GLOB_VidTimer2OCMPtrCallBack != NULL)
	{
		(*GLOB_VidTimer2OCMPtrCallBack)();
	}
}

void __vector_5(void)
{
	if (GLOB_VidTimer2OVFPtrCallBack != NULL)
	{
		(*GLOB_VidTimer2OVFPtrCallBack)();
	}
}
