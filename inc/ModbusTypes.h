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
#ifndef MODBUS_TYPES_H_
#define MODBUS_TYPES_H_

/******************************************************************************
 * Includes
 *******************************************************************************/
#include <stdint.h>
/******************************************************************************
 * Preprocessor Constants
 *******************************************************************************/
#define MODBUS_BUF_LEN 256
/******************************************************************************
 * Configuration Constants
 *******************************************************************************/

/******************************************************************************
 * Macros
 *******************************************************************************/

/******************************************************************************
 * Typedefs
 *******************************************************************************/
typedef uint16_t ModbusAddrType;
typedef uint16_t ModbusLenType;

typedef enum ModbusFunctionCode
{

    MODBUS_FC_READ_COILS = 0x01,
    MODBUS_FC_READ_DISCRETE_IN = 0x02,
    MODBUS_FC_READ_HOLD_REG = 0x03,
    MODBUS_FC_READ_IN_REG = 0x04,
    MODBUS_FC_WRITE_S_COIL = 0x05,
    MODBUS_FC_WRITE_S_HREG  = 0x06,
    MODBUS_FC_WRITE_M_COILS = 0x0F,
    MODBUS_FC_WRITE_M_HREG = 0x10,
    MODBUS_FC_ERR_OFFSET = 0x80,

} ModbusFunctionCode;

typedef struct
{
    ModbusFunctionCode funCode;
    ModbusAddrType startAddress;
    ModbusLenType byteCnt; 
} ModbusReadReq;

typedef struct
{
    ModbusFunctionCode funCode;
    ModbusLenType byteCnt; 
    uint8_t data[];
} ModbusReadErr;



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

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*MODBUS_TYPES_H_*/

/*** End of File **************************************************************/