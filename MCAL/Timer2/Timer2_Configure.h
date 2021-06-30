/*
 * Timer2_Configure.h
 *
 *  Created on: Sep 30, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_TIMER2_TIMER2_CONFIGURE_H_
#define MCAL_TIMER2_TIMER2_CONFIGURE_H_

/*****************************************************************************/
/*      					 OPTIONS FOR TIMER MODE:			             */
/*       			NORMAL - PHASE_CORRECT - CTC - FAST_PWM				     */
/*****************************************************************************/
#define MODE						PHASE_CORRECT
/*****************************************************************************/


/*****************************************************************************/
/*  OPTIONS FOR OUTPUT COMPARE PIN (OC2) BEHAVIOUR IN CASE OF NON-PWM MODE:  */
/*       		DISCONNECT_OC2 - TOGGLE_OC2 - CLEAR_OC2 - SET_OC2		     */
/*****************************************************************************/
#define OC2_NON_PWM					TOGGLE_OC2
/*****************************************************************************/


/*****************************************************************************/
/* OPTIONS FOR OUTPUT COMPARE PIN (OC2) BEHAVIOUR IN CASE OF FAST PWM MODE:  */
/*       		DISCONNECT_OC2 - NON_INVERTING_OC2 - INVERTING_OC2		     */
/*****************************************************************************/
#define OC2_FAST_PWM				NON_INVERTING_OC2
/*****************************************************************************/


/*****************************************************************************/
/* OPTIONS FOR OUTPUT COMPARE PIN (OC2) BEHAVIOUR IN CASE OF PHASE CORRECT	 */
/* 									MODE:									 */
/*       		DISCONNECT_OC2 - NON_INVERTING_OC2 - INVERTING_OC2		     */
/*****************************************************************************/
#define OC2_PHASE_CORRECT			INVERTING_OC2
/*****************************************************************************/


/*****************************************************************************/
/* 							OPTIONS FOR CLOCK SELECT	 					 */
/*        NO_CLOCK_SOURCE - NO_PRESCALER - PRESCALER_8 - PRESCALER_32	     */
/*	    PRESCALER_64 - PRESCALER_128 - PRESCALER_256  - PRESCALER_1024		 */
/*	    					  ASYNCHRONOUS_TOSC1		 					 */
/*****************************************************************************/
#define CLOCK_SELECT				PRESCALER_1024
/*****************************************************************************/


#endif /* MCAL_TIMER2_TIMER2_CONFIGURE_H_ */
