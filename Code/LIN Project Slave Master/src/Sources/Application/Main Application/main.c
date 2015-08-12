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
//#include "template.h"

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






//#include "MCU_derivative.h"


/** GPIO funtion prototypes  */

#include    "PIT.h"
#include    "LED.h"
#include	"LIN.h"
#include 	"Button.h"







void disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}



/*~~~~~~~ Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void main(void) 

{
    T_UWORD button;

	initModesAndClock();
	initPeriClkGen(); 
	/* Disable Watchdog */
	
	disableWatchdog();
	/*Initialize LEDs on TRK-MPC560xB board */
	
	INTC_InitINTCInterrupts();
	/*Initialize Interrupts */
	
	EXCEP_InitExceptionHandlers();
	/*Initialize Exception Handlers */
	
 
    /* Enable External Interrupts*/
    //enableIrq();
    
    LIN_InitSlave();
    LIN_InitMaster();
    
    LED_Driver_Init();
 	Button_Driver_Init();

  
     
 
 
   LED_OFF(LED1);
   LED_OFF(LED2);
   LED_ON(LED3);
   LED_ON(LED4);


	 for (;;) 
    {
        
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
        
  
    }

}

/*~~~~~~~ End of Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void MasterMannager()
{
	
}
void Command(T_CMD_TYPE cmd)
{
T_UBYTE State; //para que no haya error va a ser global
if(State==cmd_enable_slv)
	{
	 switch(cmd)
	        {
	        	case cmd_NONE:
	    		/* Do nothing */
	    		break;
	    	   	case cmd_LED_on:
	    		LED_ON(LED1);
	    		break;
	    		case cmd_LED_off:
	    		LED_OFF(LED1);
	    		break;
	    		case cmd_LED_toggling:
	    		LED_Toggle(LED1);
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
	cmd=cmd_NONE;
}
