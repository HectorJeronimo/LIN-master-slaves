/*******************************************************************************/
/**

\file       GPIO.h
\brief      Macro definitions for registers access and I/O handling
\author     Abraham Tezmol
\version    0.2
\date       09/05/2013
*/
/*******************************************************************************/

#ifndef _GPIO_H        /*prevent duplicated includes*/
#define _GPIO_H

/*-- Includes ----------------------------------------------------------------*/

/** Core modules */
/** MCU derivative information */
#include "MCU_derivative.h"
/** Variable types and common definitions */
#include "typedefs.h"

/*-- Variables ---------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/

/*-- Defines -----------------------------------------------------------------*/

//#define LED1      					68
//#define LED2       					69
//#define LED3       					70
//#define LED4        				71

#define GPIO_INPUT					0
#define GPIO_OUTPUT					1

#define GPIO_OPEN_DRAIN_DISABLE		0
#define GPIO_OPEN_DRAIN_ENABLE		1

/*-- Macros ------------------------------------------------------------------*/
/* Indicator LEDs handling */

/** Set LED */ 


//#define LED_ON(channel)                     (SIU.GPDO[channel].B.PDO =  0)
/** Clear LED */ 
//#define LED_OFF(channel)                    (SIU.GPDO[channel].B.PDO =  1)
/** Toggle LED */ 
//#define LED_TOGGLE(channel)                 (SIU.GPDO[channel].B.PDO ^= 1) 


/*-- Function Prototypes -----------------------------------------------------*/

void GPIO_InitChannel(T_UBYTE lub_Channel, T_UBYTE lub_InputOutput, T_UBYTE lub_OpenDrain);
void GPIO_Output(T_UBYTE lub_Channel, T_UBYTE lub_LogicalValue);
extern void GPIO_SetHigh(T_UBYTE lub_Channel);
extern void GPIO_SetLow(T_UBYTE lub_Channel);
extern void GPIO_SetInvert(T_UBYTE lub_Channel);
extern T_UBYTE GPIO_GetStatusInput(T_UBYTE lub_Channel);
extern T_UBYTE GPIO_GetStatusOutput(T_UBYTE lub_Channel);




#endif /* _GPIO_H */

/*******************************************************************************/
