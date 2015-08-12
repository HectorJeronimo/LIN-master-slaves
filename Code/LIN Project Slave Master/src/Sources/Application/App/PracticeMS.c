/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %template.c%
* Instance:         RPL_1
* %version:         2 %
* %created_by:      uid02495 %
* %date_created:    Fri Jan  9 14:38:03 2004 %
*=============================================================================*/
/* DESCRIPTION : C source template file                                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "PracticeMs.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */

 T_CMD_TYPE cmd;
 T_CMD_TYPE State;
 T_LED_STAT LED_state;

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/




/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/



void InitMS(void)
{
	 cmd =cmd_NONE;
 	State=cmd_disable_slv;
  LED_state=OFF;
}
 
 T_LED_STAT GET_LED_STATUS(void)
 {
 return LED_state;	
 }
  T_CMD_TYPE GET_STATE(void)
 {
 return State	;
 }
  void  SET_CMD(T_CMD_TYPE cmdRecived)
 {
 cmd = cmdRecived	;
 }
 
void executeMASTERTask(void)
{
	  T_UWORD button;
     button = Button_check();
 switch(button)
        {
        	case 1:
    			// MASTER_CMD_ALL MsgID = 0xCF
				LIN_TransmitDataMaster(0x030F);  
    		break;
    	   	case 2:
    			// MASTER_CMD_SLV2 MsgID = 0x11
				LIN_TransmitDataMaster(0x0311);
    		break;
    		case 3:
    			// SLAVE2_RSP MsgID = 0x61
				LIN_ReceiveDataMaster(0x0521);
    		break;
    		case 4:
    			// SLAVE2_ID MsgID = 0xB1
				LIN_ReceiveDataMaster(0x1931);
    		break;
    		default:
    		break;        
        }
	
	cmd=cmd_NONE;
}



/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
void Command(void)
{
static T_UBYTE toggleCount=0;
if(State==cmd_enable_slv || cmd ==cmd_enable_slv)
	{
	 switch(cmd)
	        {
	        	case cmd_NONE:
	    		/* Do nothing */
	    		break;
	    	   	case cmd_LED_on:
	    		LED_ON(LED1);
	    		LED_state=ON;
	    		break;
	    		case cmd_LED_off:
	    		LED_OFF(LED1);
	    		LED_state=OFF;
	    		break;
	    		case cmd_LED_toggling:
	    		if(toggleCount>127)
	    		{
	    		LED_ON(LED1);	
	    		}
	    		else
	    		{
    			LED_OFF(LED1);	
	    		}
	    		toggleCount++;
	    		LED_state=TOGGLING;
	    		break;
	    		case cmd_disable_slv:
	    		State=cmd_disable_slv;
	    		break;
	    		case cmd_enable_slv:
	    		State=cmd_enable_slv;
	    		break;
	    		default:
	    		break;        
	        }
        
	}

}
