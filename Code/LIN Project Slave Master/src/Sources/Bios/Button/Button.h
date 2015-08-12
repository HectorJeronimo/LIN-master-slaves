/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        Button.h
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri JUL 24  07:41:01 2015 
*=============================================================================*/
/* DESCRIPTION : Header file Button Driver                                    */
/*============================================================================*/
/* FUNCTION COMMENT : contains  typedef T_BUTTON_TYPE which are exported      */
/* and prototype of Button Functios                                           */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  | SAR/SIF/SCN_xxx               | Pedro R. V.      */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef BUTTON_H                               /* To avoid double inclusion */
#define BUTTON_H

/* Includes */
/* -------- */
#include "typedefs.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/* Button */



/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */


/* Functions prototypes */

extern void Button_Init(T_UBYTE lub_ID);

extern T_UBYTE Button_GetStatus(T_UBYTE  lub_Button);
extern void Button_Driver_Init(void);

/* Exported defines */
#define BUTTON1		(T_UBYTE)64
#define BUTTON2		(T_UBYTE)65
#define BUTTON3		(T_UBYTE)66
#define BUTTON4		(T_UBYTE)67





#endif


