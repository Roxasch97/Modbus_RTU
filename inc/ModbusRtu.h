/****************************************************************************
* Title                 :   ADC Application   
* Filename              :   adc_app.h
* Author                :   JWB
* Origin Date           :   06/07/2012
* Version               :   1.0.0
* Compiler              :   Microchip C30 v3.30c
* Target                :   PIC24FJ64GB004
* Notes                 :   None
*****************************************************************************/
/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description 
*  08/17/13    XXXXXXXXXXX         JWB      Interface Created.
*
*****************************************************************************/
/** \file tsk.h
 *  \brief This module contains continuous tasks.
 * 
 *  This is the header file for the definition for tasks that are continuous
 *  and should be ran as often as possible.
 */
#ifndef MODBUS_RTU_H_
#define MODBUS_RTU_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include "ModbusTypes.h"

/******************************************************************************
* Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
	
/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void modbus_master_read_hreg(ModbusAddrType addr, ModbusLenType len, uint8_t* outputBuffer);
void modbus_master_read_coils(ModbusAddrType addr, ModbusLenType len, uint8_t* outputBuffer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*MODBUS_RTU_H_*/

/*** End of File **************************************************************/