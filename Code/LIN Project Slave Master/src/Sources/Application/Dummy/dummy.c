/*******************************************************************************/
/**
\file       dummy.c
\brief      Dummy Functions
\author     Francisco Martinez
\version    1.0
\date       04/04/2014
*/
/****************************************************************************************************/

/*****************************************************************************************************
* Include files
*****************************************************************************************************/

/** Core modules */
/** Variable types and common definitions */
#include "typedefs.h"

/** Own headers */
#include "dummy.h"

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
* \brief    Turn a combination of 4 LEDs with a unique blinking pattern, this funcation shall be 
* \brief    called periodically to operate. 
* \author   Francisco Martinez
* \return   void
*/





/*******************************************************/
/*       Definicion Global de Tabla y puntero           */
TASKSTRUCT *rps_TaskPtr;
TASKSTRUCT function_table_def[] =
{
	
	{ 0, 10, &Task_5ms },
	{ 0, 20, &Task_10ms },
	{ 0, 100, &Task_50ms },
	{ 0, 200, &Task_100ms },
};
/*******************************************************/




void Test(void)
{
    static T_UWORD rub_U16Counter = 0;
    
    rub_U16Counter++;
    
    if (rub_U16Counter == 1000)
    {
    	LED_TOGGLE(LED1);
    	rub_U16Counter = 0;	
    }

}


void Task_5ms(void)
{
		LED_TOGGLE(LED1);
}
void Task_10ms(void)
{
		LED_TOGGLE(LED2);
}
void Task_50ms(void)
{
		LED_TOGGLE(LED3);	
}
void Task_100ms(void)
{
		LED_TOGGLE(LED4);	
}









void dummy_endless_loop(void)
{
rps_TaskPtr=&function_table_def[0];
/**/
for(;;)
{	
}

}





void dummy_500us(void)
{
 	auto T_SBYTE sb_Incr;
    for(sb_Incr=0;sb_Incr<4;sb_Incr++)
    {
   		 (rps_TaskPtr+sb_Incr)->ruw_Counter++;
		if((rps_TaskPtr+sb_Incr)->ruw_Counter == (rps_TaskPtr+sb_Incr)->ruw_TopCount)
		{
			(rps_TaskPtr+sb_Incr)->cpfu_PerFunct();
			(rps_TaskPtr+sb_Incr)->ruw_Counter	= 0;
		}
		
    }

}

