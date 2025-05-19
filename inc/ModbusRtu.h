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
extern "C"
{
#endif

  void modbus_master_read_hreg (uint16_t addr, uint16_t len,
                                uint8_t *outputBuffer);
  void modbus_master_read_coils (uint16_t addr, uint16_t len,
                                 uint8_t *outputBuffer);
  void modbus_master_read_discrete_in (uint16_t addr, uint16_t len,
                                       uint8_t *outputBuffer);
  void modbus_master_read_in_reg (uint16_t addr, uint16_t len,
                                  uint8_t *outputBuffer);

  void modbus_master_write_s_coil (uint16_t addr, CoilValue coilVal,
                                   uint8_t *outputBuffer);
  void modbus_master_write_s_reg (uint16_t addr, uint16_t val,
                                  uint8_t *outputBuffer);
  void modbus_master_write_multi_coils (uint16_t addr,
                                        uint16_t quantityOfCoils,
                                        uint8_t *outputBuffer,
                                        const uint8_t *inputBuffer);
  void modbus_master_write_multi_regs (uint16_t addr,
                                       uint16_t quantityOfRegisters,
                                       uint8_t *outputBuffer,
                                       const uint16_t *inputBuffer);

  void modbus_slave_read_hreg_resp (const uint8_t *requestBuffer,
                                    uint8_t *responseBuffer);
  void modbus_slave_read_coils_resp (const uint8_t *requestBuffer,
                                     uint8_t *responseBuffer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*MODBUS_RTU_H_*/

/*** End of File
 * **************************************************************/