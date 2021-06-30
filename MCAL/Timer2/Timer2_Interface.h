/*
 * Timer2_Interface.h
 *
 *  Created on: Sep 30, 2020
 *      Author: Omar Fahmy
 */


#ifndef MCAL_TIMER2_TIMER2_INTERFACE_H_
#define MCAL_TIMER2_TIMER2_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/************************************************************************************/
/*							 FUNCTIONS PROTOTYPES								    */
/************************************************************************************/

/************************************************************************************/
/* Description: initializes timer2's peripheral	  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8Init(void);
/************************************************************************************/

/************************************************************************************/
/* Description: set a value to start counting from								    */
/* Inputs: value to count from													 	*/
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8Preload(const u8 LOC_U8Value);
/************************************************************************************/

/************************************************************************************/
/* Description: set a value to compare with in non-normal modes					    */
/* Inputs: value to compare with									 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8SetCTCValue(const u8 LOC_U8Value);
/************************************************************************************/

/************************************************************************************/
/* Description: returns the value in timer2's counter. Counts are in the range of   */
/* 0 - 255.					    													*/
/* Inputs: pointer to a variable to receive the value in			 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8GetCounterValue(u8* const LOC_U8Value);
/************************************************************************************/

/************************************************************************************/
/* Description: it returns 1 if Timer2 operates asynchronously and TCNT2 is written */
/* and not yet updated. It returns 0 when TCNT2 has been updated and ready to be	*/
/* updated with a new value. If a write is performed while its update busy flag is	*/
/* set, the updated value might get corrupted and cause an unintentional interrupt	*/
/* to occur.																		*/
/* Inputs: pointer to a variable to receive the value in			 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8CheckTCNT2BusyFlag(u8* const LOC_U8Value);
/************************************************************************************/

/************************************************************************************/
/* Description: it returns 1 if Timer2 operates asynchronously and OCR2 is written  */
/* and not yet updated. It returns 0 when OCR2 has been updated and ready to be		*/
/* updated with a new value. If a write is performed while its update busy flag is	*/
/* set, the updated value might get corrupted and cause an unintentional interrupt	*/
/* to occur.																		*/
/* Inputs: pointer to a variable to receive the value in			 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8CheckOCR2BusyFlag(u8* const LOC_U8Value);
/************************************************************************************/

/************************************************************************************/
/* Description: it returns 1 if Timer2 operates asynchronously and TCCR2 is written */
/* and not yet updated. It returns 0 when TCCR2 has been updated and ready to be    */
/* updated with a new value. If a write is performed while its update busy flag is	*/
/* set, the updated value might get corrupted and cause an unintentional interrupt	*/
/* to occur.																		*/
/* Inputs: pointer to a variable to receive the value in			 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8CheckTCCR2BusyFlag(u8* const LOC_U8Value);
/************************************************************************************/

/************************************************************************************/
/* Description: enables overflow interrupt										    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8EnableOVFInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables overflow interrupt										    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8DisableOVFInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables On Compare Match interrupt								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8EnableOCMInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables On Compare Match interrupt								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 Timer2_U8DisableOCMInterrupt(void);
/************************************************************************************/

/***********************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	   */
/* triggering the overflow interrupt.  								 			   */
/* Inputs: pointer to a function that takes no arguments and returns no value	   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer2_U8OVFSetCallBack( void (*ptrToFun)(void) );
/***********************************************************************************/

/***********************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	   */
/* triggering the on compare match interrupt.						 			   */
/* Inputs: pointer to a function that takes no arguments and returns no value	   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer2_U8OCMSetCallBack( void (*ptrToFun)(void) );
/************************************************************************************/

/***********************************************************************************/
/* Description: polls on timer2 overflow's flag						 			   */
/* Inputs: nothing					   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer2_U8OVFPollingOnFlag(void);
/***********************************************************************************/

/***********************************************************************************/
/* Description: polls on timer2 on compare match's flag				 			   */
/* Inputs: nothing					   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer2_U8OCMPollingOnFlag(void);
/***********************************************************************************/


/***********************************************************************************/
/* Description: sends a PWM signal with the received duty cycle (0% - 100%) on OC2 */
/* pin. 	   																	   */
/* Inputs: analog voltage			   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer2_U8SetDutyCycle(const f32 LOC_F32DutyCycle);
/***********************************************************************************/


/***********************************************************************************/
/* Description: resets prescaler for timer2										   */
/* Inputs: nothing					   											   */
/* Output: error checking								  						   */
/***********************************************************************************/
extern u8 Timer2_U8ResetPrescaler(void);
/***********************************************************************************/


#endif /* MCAL_TIMER2_TIMER2_INTERFACE_H_ */
