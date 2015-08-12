/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        LIN_Types.h
* Instance:         RPL_1
* %version:         1.0
* %created_by:      Pedro Romero Vargas
* %date_created:    Tue Aug 04 10:48:01 2015
*=============================================================================*/
/* DESCRIPTION : Contains all the types and definitions used in LIN driver    */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to LIN driver  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 04/08/2015  | SAR/SIF/SCN_xxx               | Pedro Romero     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef LINTYPES_H                               /* To avoid double inclusion */
#define LINTYPES_H

/* Includes */
/* -------- */

#include "typedefs.h"
/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */


/* Functions macros */


/* Exported defines */








/* 





*/

#define         SIZEOFDATA       8

typedef void (*TaskFunctionPtrType)(void);



typedef enum
{
	cmd_NONE,
	cmd_LED_on,
	cmd_LED_off,
	cmd_LED_toggling,
	cmd_disable_slv,
	cmd_enable_slv
}T_CMD_TYPE; 






#endif


