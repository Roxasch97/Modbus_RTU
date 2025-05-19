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
#include "ModbusRtu.h"

#include <math.h>
#include <stdint.h>

#include "ModbusIO.h"
#include "ModbusTypes.h"
#include "ModbusUtils.h"
/******************************************************************************
 * Module Preprocessor Constants
 *******************************************************************************/

/******************************************************************************
 * Module Preprocessor Macros
 *******************************************************************************/
#define I_TO_2_BYTE_OFFSET (i * sizeof (uint16_t))
#define RESPONSE_DATA_OFFSET 2
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

static void
modbus_master_create_frame_base (ModbusFunctionCode funCode, uint16_t addr,
                                 uint16_t len, uint8_t *outputBuffer)
{
  outputBuffer[0] = funCode;
  write_u16_to_buff (outputBuffer + 1, addr);
  write_u16_to_buff (outputBuffer + 3, len);
}

static void
modbus_slave_create_frame_base (ModbusFunctionCode funCode, uint8_t byteCount,
                                uint8_t *outputBuffer)
{
  outputBuffer[0] = funCode;
  outputBuffer[1] = byteCount;
}

void
modbus_master_read_coils (uint16_t addr, uint16_t len, uint8_t *outputBuffer)
{
  modbus_master_create_frame_base (MODBUS_FC_READ_COILS, addr, len,
                                   outputBuffer);
}

void
modbus_master_read_discrete_in (uint16_t addr, uint16_t len,
                                uint8_t *outputBuffer)
{
  modbus_master_create_frame_base (MODBUS_FC_READ_DISCRETE_IN, addr, len,
                                   outputBuffer);
}

void
modbus_master_read_hreg (uint16_t addr, uint16_t len, uint8_t *outputBuffer)
{
  modbus_master_create_frame_base (MODBUS_FC_READ_HOLD_REG, addr, len,
                                   outputBuffer);
}

void
modbus_master_read_in_reg (uint16_t addr, uint16_t len, uint8_t *outputBuffer)
{
  modbus_master_create_frame_base (MODBUS_FC_READ_IN_REG, addr, len,
                                   outputBuffer);
}

void
modbus_master_write_s_coil (uint16_t addr, CoilValue coilVal,
                            uint8_t *outputBuffer)
{
  modbus_master_create_frame_base (MODBUS_FC_WRITE_S_COIL, addr, coilVal,
                                   outputBuffer);
}

void
modbus_master_write_s_reg (uint16_t addr, uint16_t val, uint8_t *outputBuffer)
{
  modbus_master_create_frame_base (MODBUS_FC_WRITE_S_HREG, addr, val,
                                   outputBuffer);
}

void
modbus_master_write_multi_coils (uint16_t addr, uint16_t quantityOfCoils,
                                 uint8_t *outputBuffer,
                                 const uint8_t *inputBuffer)
{
  uint8_t byteCount = ceil (quantityOfCoils / 8.0);
  modbus_master_create_frame_base (MODBUS_FC_WRITE_M_COILS, addr,
                                   quantityOfCoils, outputBuffer);
  outputBuffer[5] = byteCount;
  for (int i = 0; i < byteCount; i++)
    {
      outputBuffer[6 + i] = inputBuffer[i];
    }
}

void
modbus_master_write_multi_regs (uint16_t addr, uint16_t quantityOfRegisters,
                                uint8_t *outputBuffer,
                                const uint16_t *inputBuffer)
{
  uint8_t byteCount = quantityOfRegisters * 2;
  modbus_master_create_frame_base (MODBUS_FC_WRITE_M_HREG, addr,
                                   quantityOfRegisters, outputBuffer);
  outputBuffer[5] = byteCount;
  for (int i = 0; i < quantityOfRegisters; i++)
    {
      write_u16_to_buff ((outputBuffer + 6 + (i * 2)), inputBuffer[i]);
    }
}

void
modbus_slave_read_coils_resp (const uint8_t *requestBuffer,
                              uint8_t *responseBuffer)
{
  uint16_t quantityOfCoils = read_u16_from_buff (requestBuffer + 3);
  uint8_t byteCount = ((quantityOfCoils + 7) / 8);
  uint8_t startingAddress = read_u16_from_buff (requestBuffer + 1);
  modbus_slave_create_frame_base (requestBuffer[0], byteCount, responseBuffer);

  for (int i = 0; i < quantityOfCoils; i++)
    {
      responseBuffer[RESPONSE_DATA_OFFSET + i / 8]
          |= coil_get (startingAddress + i) << (i % 8);
    }
}

void
modbus_slave_read_hreg_resp (const uint8_t *requestBuffer,
                             uint8_t *responseBuffer)
{
  uint8_t quantityOfRegisters = read_u16_from_buff (requestBuffer + 3);
  uint8_t byteCount = quantityOfRegisters * 2;
  uint16_t startingAddress = read_u16_from_buff (requestBuffer + 1);
  modbus_slave_create_frame_base (requestBuffer[0], byteCount, responseBuffer);

  for (int i = 0; i < quantityOfRegisters; i++)
    {
      write_u16_to_buff (
          (responseBuffer + RESPONSE_DATA_OFFSET + I_TO_2_BYTE_OFFSET),
          hreg_get (startingAddress + i));
    }
}

/*************** END OF FUNCTIONS
 * ***************************************************************************/