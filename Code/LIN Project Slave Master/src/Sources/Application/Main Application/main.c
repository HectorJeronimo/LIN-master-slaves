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






#include "MCU_derivative.h"


/** GPIO funtion prototypes  */
#include    "GPIO.h"
#include    "PIT.h"
#include    "LED.h"
#include	"LIN.h"





static void GPIO_Init(void) 
{	
	SIU.PCR[64].R = 0x0103;
	SIU.PCR[65].R = 0x0103;
	SIU.PCR[66].R = 0x0103;
	SIU.PCR[67].R = 0x0103;
}

uint16_t button_check(void)
{
	if(SIU.GPDI[64].R==0)
	{
		while(SIU.GPDI[64].R==0){};
			
		return (1);
	}
	if(SIU.GPDI[65].R==0)
	{
		while(SIU.GPDI[65].R==0){};
			
		return (2);
	}
	if(SIU.GPDI[66].R==0)
	{
		while(SIU.GPDI[66].R==0){};
			
		return (3);
	}
	if(SIU.GPDI[67].R==0)
	{
		while(SIU.GPDI[67].R==0){};
			
		return (4);
	}
}



void disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}



/*~~~~~~~ Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void main(void) 

{
  uint32_t i = 0;
    uint16_t button;
  

	initModesAndClock();
	initPeriClkGen(); 
	/* Disable Watchdog */
	
	disableWatchdog();
	/*Initialize LEDs on TRK-MPC560xB board */
	
	INTC_InitINTCInterrupts();
	/*Initialize Interrupts */
	
	EXCEP_InitExceptionHandlers();
	/*Initialize Exception Handlers */
	
  // 	vfnGPIO_LED_Init();
	
//	PIT_device_init();
//   PIT_channel_configure(PIT_CHANNEL_0 , dummy_500us);	
//    PIT_channel_start(PIT_CHANNEL_0);F
 
    /* Enable External Interrupts*/
    //enableIrq();
    LIN_InitSlave();
    INTC_InstallINTCInterruptHandler(LIN_RX_ISR, 79, 1);
    INTC_InstallINTCInterruptHandler(LIN_TX_ISR, 80, 2);
    INTC.CPR.R = 0x0; 
    
    LED_Driver_Init();
    
 
        GPIO_Init();
       LIN_InitMaster();
 
	/*
	for (;;) 
	{
        BackgroundSubsystemTasks();
	}	
	*/

	 for (;;) 
    {
        
        button = button_check();
         
        switch(button)
        {
        	case 1:
    			// SW1 pressed, BIDR=0x1E35, Master sends 8bytes, ID=0x35, CCS=0
				LIN_TransmitDataMaster(0x030F);  
				
    		break;
    	   	case 2:
    			// SW2 pressed, BIDR=0x1F34, Master sends 8bytes, ID=0x34, CCS=1
				LIN_TransmitDataMaster(0x0311);
				
    		break;
    		case 3:
    			// SW3 pressed, BIDR=0x1C37, Master receives 8bytes, ID=0x37, CCS=0
				LIN_ReceiveDataMaster(0x0521);
				
    		break;
    		case 4:
    			// SW4 pressed, BIDR=0x1D36, Master receives 8bytes, ID=0x36, CCS=1
				LIN_ReceiveDataMaster(0x1931);
				
    		break;
    		default:
    		break;
        
        }
        
        i++;
    }

}

/*~~~~~~~ End of Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


