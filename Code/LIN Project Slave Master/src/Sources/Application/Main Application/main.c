












#include "MCU_derivative.h"


/** GPIO funtion prototypes  */
#include    "GPIO.h"
#include    "PIT.h"
#include    "LED.h"



static vuint32_t lin_bidr = 0;

static vuint32_t  rx_data[8];


static vuint32_t lin_status = 0;
static vuint32_t lin_bidrs = 0;
static vuint32_t lin_bidr_ID = 0;
static vuint32_t  rx_datas[8];
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

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/


/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

void disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}

T_UBYTE Function1(T_UBYTE *rpub_U8Ptr)
{
	return (*rpub_U8Ptr);
}   

/*****************************************************************************************************
* Definition of global wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/
    
T_UBYTE (*rpfu_PtrToFctn)(T_UBYTE *); /* Our pointer to function */ 

/******************************************************************************************************
* Definition of module wide VARIABLEs 
******************************************************************************************************/

 T_UBYTE rub_Var1 = 0xFA; 
 T_UBYTE rub_Var2; 
 T_UBYTE * rpub_PtrToU8;
 
/******************************************************************************************************
* Code of module wide FUNCTIONS
******************************************************************************************************/

void BackgroundSubsystemTasks(void);


/*****************************************/








static void LinFlex1_InitMaster(void) 
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

/*******************************************************************************
Function Name : TransmitData
Engineer      : stnp002
Date          : Sep-22-2014
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Lin Master Tx frame - example
Issues        : 
*******************************************************************************/


static void TransmitData(uint16_t bidr_value)
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

/*******************************************************************************
Function Name : ReceiveData
Engineer      : stnp002
Date          : Sep-22-2014
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Lin Master Rx frame - example
Issues        : 
*******************************************************************************/
static void ReceiveData(uint16_t bidr_value)
{
    
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










static void InitLinFlex0Slave(void) 
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
	LINFLEX_0.IFCR[1].R = 0x010F;	// 8bytes, RX data, ID=0x35, CCS=0
	
	LINFLEX_0.IFCR[2].R = 0x1B31; // 8bytes, TX data, ID=0x36, CCS=1
	LINFLEX_0.IFCR[3].R = 0x0111;	// 8bytes, RX data, ID=0x34, CCS=1
	
	LINFLEX_0.LINIER.R = 0x7;	// enable RX, TX and header interrupt
	
	LINFLEX_0.LINCR1.R = 0x2300;
  
    
}


static void LINFlex_0_RX_ISR(void)
{
	lin_status = LINFLEX_0.LINSR.R;
		/* wait for RMB */
	while (1 != LINFLEX_0.LINSR.B.RMB) {}  /* Wait for Release Message Buffer */
	
	/* get the data */
    rx_datas[0] = LINFLEX_0.BDRL.B.DATA0;   // se recive un comando que se guarda en una variale para despues ser ejecutado------------
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



static void LINFlex_0_TX_ISR(void)
{
	static uint32_t toggle = 0;

	lin_status = LINFLEX_0.LINSR.R;
	lin_bidrs = LINFLEX_0.BIDR.R;
    lin_bidr_ID = lin_bidr&0x3F;
	
	if(lin_status&0x1)		/* if header received */
	{
	//	SIU.GPDO[68].R = 0x0;
		
	//	LINFLEX_0.LINSR.R = 0x1;
		
		LINFLEX_0.BIDR.B.DIR = 0; /* BDR direction - write */
    
    //	if(lin_bidr_ID==0x37) LINFLEX_0.BIDR.B.CCS = 0; /* enhanced checksum for LIN Slave */
    //	if(lin_bidr_ID==0x36) LINFLEX_0.BIDR.B.CCS = 1; /* classic checksum for LIN Slave */
    
	    /* fill the BDR registers */
	    // ---------------------------------------------------------------------------funcion que escogeque se envia dependiendo del id 
	    LINFLEX_0.BDRL.B.DATA0 = toggle;
	    LINFLEX_0.BDRL.B.DATA1 = 0x55;
	    LINFLEX_0.BDRL.B.DATA2 = 0xAA;
	    LINFLEX_0.BDRL.B.DATA3 = 0x55;
	    LINFLEX_0.BDRM.B.DATA4 = 'o';
	    LINFLEX_0.BDRM.B.DATA5 = ' ';
	    LINFLEX_0.BDRM.B.DATA6 = ',';
	    LINFLEX_0.BDRM.B.DATA7 = ' ';
	        
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


/*~~~~~~~ Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main(void) 

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
    InitLinFlex0Slave();
    INTC_InstallINTCInterruptHandler(LINFlex_0_RX_ISR, 79, 1);
    INTC_InstallINTCInterruptHandler(LINFlex_0_TX_ISR, 80, 2);
    INTC.CPR.R = 0x0; 
    
    LED_Driver_Init();
    
 
        GPIO_Init();
       LinFlex1_InitMaster();
 
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
				TransmitData(0x030F);  
				
    		break;
    	   	case 2:
    			// SW2 pressed, BIDR=0x1F34, Master sends 8bytes, ID=0x34, CCS=1
				TransmitData(0x0311);
				
    		break;
    		case 3:
    			// SW3 pressed, BIDR=0x1C37, Master receives 8bytes, ID=0x37, CCS=0
				ReceiveData(0x0521);
				
    		break;
    		case 4:
    			// SW4 pressed, BIDR=0x1D36, Master receives 8bytes, ID=0x36, CCS=1
				ReceiveData(0x1931);
				
    		break;
    		default:
    		break;
        
        }
        
        i++;
    }

}

/*~~~~~~~ End of Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Background tasks related to Subsystem control */
void BackgroundSubsystemTasks(void) 
{
	rpub_PtrToU8 = &rub_Var1; /* We need to initialize the pointer to be used by our function invocation */

    rpfu_PtrToFctn = &Function1; /* Let's perform our deferencing procedure (initialization) */

    /* Let's first call our function through direct invocation */
    rub_Var2 = Function1(rpub_PtrToU8);
    
    /* Clear var2 in preparation to next invocation */
    rub_Var2 = 0;

    /* Now, perform invocation through our pointer */
    rub_Var2 = rpfu_PtrToFctn(rpub_PtrToU8);

    /* See, I told you, pointers to functions are FUN !! */;
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


