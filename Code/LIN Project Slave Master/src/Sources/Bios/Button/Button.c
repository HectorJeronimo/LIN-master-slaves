/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         Button.c
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri Jul 24  14:38:03 2015 
*=============================================================================*/
/* DESCRIPTION : C source Button Driver                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source from the Button driver */
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

#include "Button.h"
#include "GPIO.h"





/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	Button_Init
 *  Description          : Initialize a Button Type
 *  Parameters           : S_BUTTON_TYPE *  , T_UBYTE 
 *  Return               : void
 *  Critical/explanation : No
 **************************************************************/

void Button_Init(T_UBYTE lub_ID )
{
    /* Data Port A initialization */ 
	GPIO_InitChannel(lub_ID,GPIO_INPUT,GPIO_OPEN_DRAIN_DISABLE);  	
}

void Button_Driver_Init(void)
{
	Button_Init(BUTTON1);
	Button_Init(BUTTON2);
	Button_Init(BUTTON3);
	Button_Init(BUTTON4);
	
}

/**************************************************************
 *  Name                 :	Button_GetStatus
 *  Description          :	Get the Statuus of a button
 *  Parameters           :  S_BUTTON_TYPE* 
 *  Return               :	T_UBYTE
 *  Critical/explanation :	No
 **************************************************************/

T_UBYTE Button_GetStatus(T_UBYTE lps_Button)
{
	return GPIO_GetStatusInput(lps_Button);
}

