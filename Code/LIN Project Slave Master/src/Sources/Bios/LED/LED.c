/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         LED.c
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri Jul 24  14:38:03 2015 
*=============================================================================*/
/* DESCRIPTION : C source LED Driver                                          */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source from the LED driver    */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  |                               | Pedro R. V.      */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "LED.h"
#include "GPIO.h"


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 
#define LED1		68
#define LED2		69
#define LED3		70
#define LED4		71



/* Exported functions prototypes */
/* ----------------------------- */


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	LED_Init
 *  Description          :	Initialize a LED type
 *  Parameters           :  T_LED_TYPE * , T_UBYTE
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void LED_Init( T_UBYTE lub_ID)
{
	GPIO_InitChannel(lub_ID,GPIO_OUTPUT,GPIO_OPEN_DRAIN_DISABLE);  
	GPIO_Output (lub_ID, 1);	
}


/**************************************************************
 *  Name                 :	LED_ON
 *  Description          :	Turn ON a LED
 *  Parameters           :  T_LED_TYPE*
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void LED_ON(T_LED_TYPE lt_Led)
{
	GPIO_SetHigh(lt_Led);
}


/**************************************************************
 *  Name                 :	LED_OFF
 *  Description          :	Turn OFF a LED
 *  Parameters           :  T_LED_TYPE*
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void LED_OFF(T_LED_TYPE lt_Led)
{
	GPIO_SetLow(lt_Led);
}


/**************************************************************
 *  Name                 :	LED_Toggle
 *  Description          :	Toggle a LED
 *  Parameters           :  T_LED_TYPE*
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void LED_Toggle(T_LED_TYPE lt_Led)
{
	GPIO_SetInvert(lt_Led);
}



/**************************************************************
 *  Name                 :	LED_GetStatus
 *  Description          :	Get the status of a LED
 *  Parameters           :  T_LED_TYPE*
 *  Return               :	T_UBYTE
 *  Critical/explanation :  No
 **************************************************************/
T_UBYTE LED_GetStatus(T_LED_TYPE lt_Led)
{
	return GPIO_GetStatusOutput(lt_Led);
}




void LED_Driver_Init(void)
{
    LED_Init(LED1);
    LED_Init(LED2);
    LED_Init(LED3);
    LED_Init(LED4);	
}

