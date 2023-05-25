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
#include <math.h>
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

static void modbus_create_frame_base(ModbusFunctionCode funCode, uint16_t addr, uint16_t len_val, uint8_t* outputBuffer)
{
    outputBuffer[0] = funCode;
    write_u16_to_buff(outputBuffer+1, addr);
    write_u16_to_buff(outputBuffer+3, len_val);
}

void modbus_master_read_coils(uint16_t addr, uint16_t len, uint8_t* outputBuffer)
{
    modbus_create_frame_base(MODBUS_FC_READ_COILS, addr, len, outputBuffer);
}

void modbus_master_read_discrete_in(uint16_t addr, uint16_t len, uint8_t* outputBuffer)
{
    modbus_create_frame_base(MODBUS_FC_READ_DISCRETE_IN, addr, len, outputBuffer);
}

void modbus_master_read_hreg(uint16_t addr, uint16_t len, uint8_t* outputBuffer)
{
    modbus_create_frame_base(MODBUS_FC_READ_HOLD_REG, addr, len, outputBuffer);
}

void modbus_master_read_in_reg(uint16_t addr, uint16_t len, uint8_t* outputBuffer)
{
    modbus_create_frame_base(MODBUS_FC_READ_IN_REG, addr, len, outputBuffer);
}

void modbus_master_write_s_coil(uint16_t addr, CoilValue coilVal, uint8_t* outputBuffer)
{
    modbus_create_frame_base(MODBUS_FC_WRITE_S_COIL, addr, coilVal, outputBuffer);
}

void modbus_master_write_s_reg(uint16_t addr, uint16_t val, uint8_t* outputBuffer)
{
    modbus_create_frame_base(MODBUS_FC_WRITE_S_HREG, addr, val, outputBuffer);
}

void modbus_master_write_multi_coils(uint16_t addr, uint16_t quantityOfCoils, uint8_t* outputBuffer, const uint8_t* inputBuffer)
{
    uint8_t byteCount = ceil(quantityOfCoils/8.0);
    modbus_create_frame_base(MODBUS_FC_WRITE_M_COILS, addr, quantityOfCoils, outputBuffer);
    outputBuffer[5] = byteCount;
    for(int i = 0; i<byteCount; i++)
    {
        outputBuffer[6+i] = inputBuffer[i];
    }
}

void modbus_master_write_multi_regs(uint16_t addr, uint16_t quantityOfRegisters, uint8_t* outputBuffer, const uint16_t* inputBuffer)
{
    uint8_t byteCount = quantityOfRegisters*2;
    modbus_create_frame_base(MODBUS_FC_WRITE_M_HREG, addr, quantityOfRegisters, outputBuffer);
    outputBuffer[5] = byteCount;
    for(int i = 0; i<quantityOfRegisters; i++)
    {
        write_u16_to_buff((outputBuffer+6+(i*2)), inputBuffer[i]);
    }
}

/*************** END OF FUNCTIONS ***************************************************************************/