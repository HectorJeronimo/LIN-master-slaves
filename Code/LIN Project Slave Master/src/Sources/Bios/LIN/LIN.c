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
#include "LIN.h"
#include "PracticeMS.h"

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


 void LIN_InitMaster(void) 
{	

    /* enter INIT mode */
    LINFLEX_1.LINCR1.R = 0x0081; /* SLEEP=0, INIT=1 */
	
    /* wait for the INIT mode */
    while (0x1000 != (LINFLEX_1.LINSR.R & 0xF000)) {}
		
    /* configure pads */
    SIU.PCR[38].R = 0x0604;     /* Configure pad PB2 for AF1 func: LIN0TX */
    SIU.PCR[39].R = 0x0100;     /* Configure pad PB3 for LIN0RX */
    
    /* configure baudrate 9600 */
    /* assuming 64 MHz peripheral set 1 clock */		
    LINFLEX_1.LINFBRR.R = 11;
    LINFLEX_1.LINIBRR.R = 416;
        
    LINFLEX_1.LINCR2.R = 0x20; /* IOBE=1, Bit error resets LIN state machine */
   //  LINFLEX_1.LINCR2.B.IOPE =0x1;
    LINFLEX_1.LINTCSR.R = 0;	/* LIN timeout mode, no idle on timeout */
		
    /* enter NORMAL mode */
    /* CCD bit 16 = 0 ... checksum calculation by hardware
       CFD bit 17 = 0 ... checksum field is sent after the required number 
                    of data bytes is sent
       LASE bit 18 = 0 ... Slave automatic resync disable
       AWUM bit 19 = 0 ... The sleep mode is exited on software request
       MBL bits 20:23 = 0b0011 ... 13-bit LIN Master break length
       BF bit 24 = 1 ... An RX interrupt is generated on identifier not matching any filter
       SFTM bit 25 = 0 ... Self Test mode disable
       LBKM bit 26 = 0 ... Loop Back mode disable
       MME bit 27 = 1 ... Master mode
       SBDT bit 28 = 0 ... 11-bit Slave Mode break threshold
       RBLM bit 29 = 0 ... Receive Buffer not locked on overrun
       SLEEP bit 30 = 0
       INIT bit 31 = 0 ... entering Normal mode
       =
       0x0390 
     */
    LINFLEX_1.LINCR1.R = 0x0390;
    
    //LINFLEX_1.BIDR.B.CCS = 0; /* enhanced checksum for LIN Slave */
}







void LIN_TransmitDataMaster(uint16_t bidr_value)
{
    /* store the data in the message buffer BDR */
    
    LINFLEX_1.BDRL.B.DATA0 = 'H';  // enviar un commando destinado de un dipswitch
    //LINFLEX_1.BDRL.B.DATA1 = 'e';
   // LINFLEX_1.BDRL.B.DATA2 = 'l';
  //  LINFLEX_1.BDRL.B.DATA3 = 'l';
    
    //LINFLEX_1.BDRM.B.DATA4 = 'o';
    //LINFLEX_1.BDRM.B.DATA5 = ' ';
   // LINFLEX_1.BDRM.B.DATA6 = ',';
   // LINFLEX_1.BDRM.B.DATA7 = ' ';

	/* Master to publish x bytes with ID and CCS from bidr_value */
    LINFLEX_1.BIDR.R = bidr_value; //0x1E35;
    
    /* Trigger Frame transmission */
    LINFLEX_1.LINCR2.B.HTRQ = 1;    
    
    /* wait until Master response to the LIN header has been sent successfully */
    while(0 == LINFLEX_1.LINSR.B.DTF) 
    {
        /* track LIN Status for errors */
  
    }
    
    LINFLEX_1.LINSR.R = 0x0002; /* clear the DTF bit */

}


void LIN_ReceiveDataMaster(uint16_t bidr_value)
{
    static vuint32_t  rx_data[8];
    /* Master to receive x bytes with ID and CCS from bidr_value */
    LINFLEX_1.BIDR.R = bidr_value; 

    /* Trigger Frame transmission */
    LINFLEX_1.LINCR2.B.HTRQ = 1;    
    
    /* wait until Slave response to the LIN header has been receive successfully */
    while(0 == LINFLEX_1.LINSR.B.DRF) 
    {
        /* track LIN Status for errors */
  
    }
    
    
    //if (id es ID )  else (id = status) //pero procesar esa data no es importante
    	/* read BDR registers */
    	rx_data[0] = LINFLEX_1.BDRL.B.DATA0;
    	rx_data[1] = LINFLEX_1.BDRL.B.DATA1;
    	rx_data[2] = LINFLEX_1.BDRL.B.DATA2;
    	rx_data[3] = LINFLEX_1.BDRL.B.DATA3;
    	rx_data[4] = LINFLEX_1.BDRM.B.DATA4;
    	rx_data[5] = LINFLEX_1.BDRM.B.DATA5;
    	rx_data[6] = LINFLEX_1.BDRM.B.DATA6;
    	rx_data[7] = LINFLEX_1.BDRM.B.DATA7;
    
    /* clear RMB, HRF, DRF and DTF flags */    
    LINFLEX_1.LINSR.R = 0x0207;
    
}










void LIN_InitSlave(void) 
{	
	

	
    /* enter INIT mode */
    LINFLEX_0.LINCR1.R = 0x0081; /* SLEEP=0, INIT=1 */
	
    /* wait for the INIT mode */
    while (0x1000 != (LINFLEX_0.LINSR.R & 0xF000)) {}
	
	/* configure pads */
    SIU.PCR[18].R = 0x0604;     /* Configure pad PB2 for AF1 func: LIN0TX */
    SIU.PCR[19].R = 0x0100;     /* Configure pad PB3 for LIN0RX */
    
    /* configure baudrate 19200 */
    /* assuming 64 MHz peripheral set 1 clock */		
    LINFLEX_0.LINFBRR.R = 11;
    LINFLEX_0.LINIBRR.R = 416;
        
    LINFLEX_0.LINCR2.R = 0x20; /* IOBE=1, Bit error resets LIN state machine */
    
    LINFLEX_0.LINTCSR.R = 0; /* LIN timeout mode, no idle on timeout */

//	LINFLEX_0.BIDR.B.CCS = 0; /* enhanced checksum for LIN Slave */


	LINFLEX_0.IFER.R = 0xF;		// enable filters 0-3
	LINFLEX_0.IFMR.R = 0x0;		// filters 0 - 3 are in identifier list mode.
	
	LINFLEX_0.IFCR[0].R = 0x0721;	// 8bytes, TX data, ID=0x37, CCS=0
	LINFLEX_0.IFCR[1].R = 0x010F;	// 010f 8bytes, RX data, ID=0x35, CCS=0
	
	LINFLEX_0.IFCR[2].R = 0x1B31; // 8bytes, TX data, ID=0x36, CCS=1
	LINFLEX_0.IFCR[3].R = 0x0111;	// 8bytes, RX data, ID=0x34, CCS=1
	
	LINFLEX_0.LINIER.R = 0x7;	// enable RX, TX and header interrupt

   INTC_InstallINTCInterruptHandler(LIN_RX_ISR, 79, 1);
   INTC_InstallINTCInterruptHandler(LIN_TX_ISR, 80, 2);
   INTC.CPR.R = 0x0; 
   
	LINFLEX_0.LINCR1.R = 0x2300;

    
}


void LIN_RX_ISR(void)
{
static vuint32_t  rx_datas[8];
T_CMD_TYPE cmd_Recive;
	static vuint32_t lin_status = 0;
	lin_status = LINFLEX_0.LINSR.R;
		/* wait for RMB */
	while (1 != LINFLEX_0.LINSR.B.RMB) {}  /* Wait for Release Message Buffer */
	
	/* get the data */
    rx_datas[0] = LINFLEX_0.BDRL.B.DATA0;   // se recive un comando que se guarda en una variale para despues ser ejecutado------------
    cmd_Recive =(T_CMD_TYPE)rx_datas[0];
    SET_CMD((T_CMD_TYPE)rx_datas[0]);

  //  rx_datas[1] = LINFLEX_0.BDRL.B.DATA1;
  //  rx_datas[2] = LINFLEX_0.BDRL.B.DATA2;
  //  rx_datas[3] = LINFLEX_0.BDRL.B.DATA3;
  //  rx_datas[4] = LINFLEX_0.BDRM.B.DATA4;
  //  rx_datas[5] = LINFLEX_0.BDRM.B.DATA5;
 //   rx_datas[6] = LINFLEX_0.BDRM.B.DATA6;
//    rx_datas[7] = LINFLEX_0.BDRM.B.DATA7;

	/* clear the DRF and RMB flags by writing 1 to them */
	LINFLEX_0.LINSR.R = 0x0205;



}



void LIN_TX_ISR(void)
{

static vuint32_t lin_bidrs = 0;
static vuint32_t lin_bidr_ID = 0;
	static vuint32_t lin_status = 0;
	static uint32_t toggle = 0;

	lin_status = LINFLEX_0.LINSR.R;
	lin_bidrs = LINFLEX_0.BIDR.R;
    lin_bidr_ID = lin_bidrs&0x3F;
	
	if(lin_status&0x1)		/* if header received */
	{
	//	SIU.GPDO[68].R = 0x0;
		
	//	LINFLEX_0.LINSR.R = 0x1;
		
		LINFLEX_0.BIDR.B.DIR = 0; /* BDR direction - write */
    
    //	if(lin_bidr_ID==0x37) LINFLEX_0.BIDR.B.CCS = 0; /* enhanced checksum for LIN Slave */
    //	if(lin_bidr_ID==0x36) LINFLEX_0.BIDR.B.CCS = 1; /* classic checksum for LIN Slave */
    
	    /* fill the BDR registers */
	    // ---------------------------------------------------------------------------funcion que escogeque se envia dependiendo del id 
	    if(lin_bidr_ID == 0x21)
	    {
	  LINFLEX_0.BDRL.B.DATA0 = (T_UBYTE)GET_STATE();
	    LINFLEX_0.BDRL.B.DATA1 = (T_UBYTE)GET_LED_STATUS();
	    }
	    else
	    {
	  
	    
	         LINFLEX_0.BDRL.B.DATA0 = 0x02;
	    LINFLEX_0.BDRL.B.DATA1 = 'P';
	    LINFLEX_0.BDRL.B.DATA2 = 'H';
	    LINFLEX_0.BDRL.B.DATA3 = 'R';
	    LINFLEX_0.BDRM.B.DATA4 = 'C';
	    LINFLEX_0.BDRM.B.DATA5 = 'V';
	    LINFLEX_0.BDRM.B.DATA6 = 'V';
	   // LINFLEX_0.BDRM.B.DATA7 = ' ';	
	    }
	   
	        
	    /* specify the data field length BIDR[DFL] */
	//  LINFLEX_0.BIDR.B.DFL = 0x07; /* 8 bytes - 1 */        
	    
	    /* trigger the data transmission */
	   	LINFLEX_0.LINCR2.B.DTRQ = 1;
		LINFLEX_0.LINSR.R = 0x1;	
	}
	
	if(lin_status&0x2)	/* if data transmitted */
	{
//		SIU.GPDO[68].R = 0x1;
		
		LINFLEX_0.LINSR.R = 0x2;
		
		/* toggle dat for next frame */
    	if(toggle==0) toggle = 1;
    	else toggle = 0;
	}
	
}
