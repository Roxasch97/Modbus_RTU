/*******************************************************************************
* Title                 :   System Initialization
* Filename              :   sys_init.c
* Author                :   JWB
* Origin Date           :   04/23/2012
* Version               :   1.0.0
* Compiler              :   Microchip C30 v3.30c
* Target                :   PIC24FJ64GB004
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description 
*  XX/XX/XX    XXXXXXXXXXX         JWB      Module Created.
*
*******************************************************************************/
/** \file XXX.c
 * \brief This module contains the 
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include <stdint.h>					// For portable types
#include "ModbusRtu.h"
#include "ModbusTypes.h"
#include "ModbusUtils.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
void modbus_master_read_hreg(ModbusAddrType addr, ModbusLenType len, uint8_t* outputBuffer)
{
    outputBuffer[0] = MODBUS_FC_READ_HOLD_REG;
    write_u16_to_buff(outputBuffer+1, addr);
    write_u16_to_buff(outputBuffer+3, len);
}

void modbus_master_read_coils(ModbusAddrType addr, ModbusLenType len, uint8_t* outputBuffer)
{
    outputBuffer[0] = MODBUS_FC_READ_COILS;
    write_u16_to_buff(outputBuffer+1, addr);
    write_u16_to_buff(outputBuffer+3, len);
}

void modbus_master_read_discrete_in(ModbusAddrType addr, ModbusLenType len, uint8_t* outputBuffer)
{
    outputBuffer[0] = MODBUS_FC_READ_DISCRETE_IN;
    write_u16_to_buff(outputBuffer+1, addr);
    write_u16_to_buff(outputBuffer+3, len);
}

/*************** END OF FUNCTIONS ***************************************************************************/