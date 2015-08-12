/*******************************************************************************/
/**
\file       GPIO.c
\brief      General purpose IO functions
\author     Abraham Tezmol
\version    1.0
\date       31/10/2008
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** MCU derivative information */
#include "MCU_derivative.h"
/** Variable types and common definitions */
#include "typedefs.h"

/** Own headers */
/* GPIO routines prototypes */ 
#include "GPIO.h"

/** Used modules */


/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs 
*****************************************************************************************************/

/*****************************************************************************************************
* Code of module wide FUNCTIONS
*****************************************************************************************************/


/****************************************************************************************************/
/**
* \brief    Configures individual GPIO pins to either input or output functionality.  
* \author   Abraham Tezmol
* \param    uint8_t lub_Channel - GPIO lub_Channel to be configured
* \param    uint8_t input_output - selection of input/output functionality (has impact on output impedance selection)
* \param    uint8_t Open_drain - Push pull or open drain selection modes 
* \return   void
*/

void GPIO_InitChannel(T_UBYTE lub_Channel, T_UBYTE lub_InputOutput, T_UBYTE lub_OpenDrain)
{
    if (lub_InputOutput == GPIO_OUTPUT)
    {
    	SIU.PCR[lub_Channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[lub_Channel].B.OBE = 1;					/* Output buffer enable */
    	if (lub_OpenDrain == GPIO_OPEN_DRAIN_ENABLE)
    	{
    		SIU.PCR[lub_Channel].B.ODE = 1;				/* Open drain option enable */	
    	}
    	else
    	{	
    		SIU.PCR[lub_Channel].B.ODE = 0;				/* Push-pull option enable */	
    	}
    }
    else if (lub_InputOutput == GPIO_INPUT)
    {
    	SIU.PCR[lub_Channel].B.PA  = 0;  				/* GPIO */
    	SIU.PCR[lub_Channel].B.IBE = 1;					/* Input buffer enable */	
    }

}

/****************************************************************************************************/
/**
* \brief    Configures individual GPIO pins to either input or output functionality.  
* \author   Abraham Tezmol
* \param    uint8_t lub_Channel - GPIO lub_Channel to be configured
* \param    uint8_t input_output - selection of input/output functionality (has impact on output impedance selection)
* \param    uint8_t Open_drain - Push pull or open drain selection modes 
* \return   void
*/
void GPIO_Output(T_UBYTE lub_Channel, T_UBYTE ub_LogicalValue)
{
    SIU.GPDO[lub_Channel].B.PDO  = ub_LogicalValue;  		/* Drive the logical output value to the pin */

}




 void GPIO_SetHigh(T_UBYTE lub_Channel)
{
	SIU.GPDO[lub_Channel].B.PDO =  1;		
}

 void GPIO_SetLow(T_UBYTE lub_Channel)
{
	SIU.GPDO[lub_Channel].B.PDO =  0;		
}

 void GPIO_SetInvert(T_UBYTE lub_Channel)
{
	SIU.GPDO[lub_Channel].B.PDO ^=  1;		
}

T_UBYTE GPIO_GetStatusOutput(T_UBYTE lub_Channel)
{
	return SIU.GPDO[lub_Channel].B.PDO;		
}


T_UBYTE GPIO_GetStatusInput(T_UBYTE lub_Channel)
{
	return !SIU.GPDI[lub_Channel].R;		
}