#include "gtest/gtest.h"
#include "ModbusRtu.h"
#include "ModbusUtils.h"


namespace {

class ModbusRequestsTest : public testing::Test
{
    protected:

    void SetUp() override
    {
        memset(outputBuffer, 0, sizeof(uint8_t)*MODBUS_BUF_LEN);
    }

    void TearDown() override
    {

    }
    uint8_t outputBuffer[MODBUS_BUF_LEN] = {0};
};

TEST_F(ModbusRequestsTest, readHregTest)
{
    uint16_t addr = 0x01;
    uint16_t len = 1;

    modbus_master_read_hreg(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_HOLD_REG, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(len, read_u16_from_buff(outputBuffer+3));
    
    for(int i = 5; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

TEST_F(ModbusRequestsTest, readCoilsTest)
{
    uint16_t addr = 0x01;
    uint16_t len = 1;

    modbus_master_read_coils(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_COILS, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(len, read_u16_from_buff(outputBuffer+3));

    for(int i = 5; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

TEST_F(ModbusRequestsTest, readDiscreteIn)
{
    uint16_t addr = 0x01;
    uint16_t len = 1;

    modbus_master_read_discrete_in(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_DISCRETE_IN, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(len, read_u16_from_buff(outputBuffer+3));

    for(int i = 5; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

TEST_F(ModbusRequestsTest, readInReg)
{
    uint16_t addr = 0x01;
    uint16_t len = 1;

    modbus_master_read_in_reg(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_IN_REG, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(len, read_u16_from_buff(outputBuffer+3));

    for(int i = 5; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

TEST_F(ModbusRequestsTest, writeSingleCoilOn)
{
    uint16_t addr = 0x01;
    
    modbus_master_write_s_coil(addr, MODBUS_COIL_ON, outputBuffer);

    ASSERT_EQ(MODBUS_FC_WRITE_S_COIL, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(MODBUS_COIL_ON, read_u16_from_buff(outputBuffer+3));

    for(int i = 5; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

TEST_F(ModbusRequestsTest, writeSingleCoilOFF)
{
    uint16_t addr = 0x01;
    
    modbus_master_write_s_coil(addr, MODBUS_COIL_OFF, outputBuffer);

    ASSERT_EQ(MODBUS_FC_WRITE_S_COIL, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(MODBUS_COIL_OFF, read_u16_from_buff(outputBuffer+3));

    for(int i = 5; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

TEST_F(ModbusRequestsTest, writeSingleRegister)
{
    uint16_t addr = 0x01;
    uint16_t val = 0x4B1D;
    
    modbus_master_write_s_reg(addr, val, outputBuffer);

    ASSERT_EQ(MODBUS_FC_WRITE_S_HREG, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(val, read_u16_from_buff(outputBuffer+3));

    for(int i = 5; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

TEST_F(ModbusRequestsTest, writeMultiCoils)
{
    uint16_t addr = 0x01;
    uint8_t vals[2] = {0xAA, 0xFF};
    uint16_t quantityOfCoils = 16;
    
    modbus_master_write_multi_coils(addr, quantityOfCoils, outputBuffer, vals);

    ASSERT_EQ(MODBUS_FC_WRITE_M_COILS, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(quantityOfCoils, read_u16_from_buff(outputBuffer+3));
    ASSERT_EQ(outputBuffer[6], vals[0]);
    ASSERT_EQ(outputBuffer[7], vals[1]);

    for(int i = 10; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

TEST_F(ModbusRequestsTest, writeMultiHregs)
{
    uint16_t addr = 0x01;
    uint16_t vals[2] = {0x4B1D, 0xB4F8};
    uint16_t quantityOfRegs = 2;
    uint8_t byteCount = 2*quantityOfRegs;
    
    modbus_master_write_multi_regs(addr, quantityOfRegs, outputBuffer, vals);

    ASSERT_EQ(MODBUS_FC_WRITE_M_HREG, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(quantityOfRegs, read_u16_from_buff(outputBuffer+3));
    ASSERT_EQ(byteCount, outputBuffer[5]);
    ASSERT_EQ(read_u16_from_buff(outputBuffer+6), vals[0]);
    ASSERT_EQ(read_u16_from_buff(outputBuffer+8), vals[1]);

    for(int i = 10; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(outputBuffer[i], 0);
    }
}

}
