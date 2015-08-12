/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        LED.h
* Instance:         RPL_1
* %version:         1 
* %created_by:      Pedro Romero Vargas
* %date_created:    Fri JUL 24  07:41:01 2015 
*=============================================================================*/
/* DESCRIPTION : Header file LED Driver                                       */
/*============================================================================*/
/* FUNCTION COMMENT : contains  typedef T_LED_TYPE which are exported         */
/* and prototype of LED Functios                                              */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 24/07/2015  | SAR/SIF/SCN_xxx               | Pedro R. V.      */
/* Integration under Continuus CM                                             */
/*============================================================================*/

#ifndef LEDS_H                               /* To avoid double inclusion */
#define LEDS_H

/* Includes */
/* -------- */

#include "typedefs.h"


/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */

typedef T_UBYTE T_LED_TYPE; 
#define LED1		68
#define LED2		69
#define LED3		70
#define LED4		71




/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void LED_Init(T_UBYTE lub_ID);
extern void LED_ON(T_LED_TYPE  lt_Led);
extern void LED_OFF(T_LED_TYPE  lt_Led);
extern void LED_Toggle(T_LED_TYPE  lt_Led);
extern T_UBYTE LED_GetStatus(T_LED_TYPE  lt_Led);
extern void LED_Driver_Init(void);




#endif


