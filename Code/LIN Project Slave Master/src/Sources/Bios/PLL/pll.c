
/* MCU-specific derivative */
#include "MCU_derivative.h" 
/* Data types */
#include "typedefs.h"

void initModesAndClock(void) 
{

  ME.MER.R = 0x0000001D;        /* Enable DRUN, RUN0, SAFE, RESET modes */
                                  /* Initialize PLL before turning it on: */
    /* Use 1 of the next 2 lines depending on crystal frequency: */
    CGM.FMPLL_CR.R = 0x02400100; /* 8 MHz xtal: Set PLL0 to 64 MHz */   
    /*CGM.FMPLL[0].CR.R = 0x12400100;*//* 40 MHz xtal: Set PLL0 to 64 MHz */   
    ME.RUN[0].R = 0x001F0074;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */
    ME.RUNPC[0].R = 0x00000010; 	  /* Peri. Cfg. 0 settings: only run in RUN0 mode */
    /* Use the next lines as needed for MPC56xxB/S: */  	    	
    ME.PCTL[48].R = 0x0000;         /* MPC56xxB LINFlex0: select ME.RUNPC[0] */	
    ME.PCTL[49].R = 0x0000;    
    ME.PCTL[68].R = 0x0000;         /* MPC56xxB/S SIUL:  select ME.RUNPC[0] */	

    /* Mode Transition to enter RUN0 mode: */
    ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
    ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
    while (ME.IS.B.I_MTC != 1) {}    /* Wait for mode transition to complete */    
    ME.IS.R = 0x00000001;           /* Clear Transition flag */    
									
}

void initPeriClkGen(void) 
{
CGM.SC_DC[0].R = 0x80;   /* MPC56xxB/S: Enable peri set 1 sysclk divided by 1 */
}
