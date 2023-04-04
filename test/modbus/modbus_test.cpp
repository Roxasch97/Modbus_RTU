#include "gtest/gtest.h"
#include "ModbusRtu.h"
#include "ModbusUtils.h"

using testing::Test;

namespace {

class ModbusTest : public testing::Test
{
    protected:

    void SetUp() override
    {
        memset(outputBuffer, 0, sizeof(uint8_t)*MODBUS_BUF_LEN);
    }

    void TearDown() override
    {

    }
    uint8_t outputBuffer[MODBUS_BUF_LEN];
};

TEST_F(ModbusTest, readHregTest)
{
    uint16_t addr = 0x01;
    uint16_t len = 1;

    modbus_master_read_hreg(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_HOLD_REG, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(len, read_u16_from_buff(outputBuffer+3));
}

TEST_F(ModbusTest, readCoilsTest)
{
    uint16_t addr = 0x01;
    uint16_t len = 1;

    modbus_master_read_coils(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_COILS, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(len, read_u16_from_buff(outputBuffer+3));
}

TEST_F(ModbusTest, readDiscreteIn)
{
    uint16_t addr = 0x01;
    uint16_t len = 1;

    modbus_master_read_discrete_in(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_DISCRETE_IN, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(len, read_u16_from_buff(outputBuffer+3));
}

TEST_F(ModbusTest, readInReg)
{
    uint16_t addr = 0x01;
    uint16_t len = 1;

    modbus_master_read_in_reg(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_IN_REG, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(len, read_u16_from_buff(outputBuffer+3));
}

TEST_F(ModbusTest, writeSingleCoilOn)
{
    uint16_t addr = 0x01;
    
    modbus_master_write_s_coil(addr, MODBUS_COIL_ON, outputBuffer);

    ASSERT_EQ(MODBUS_FC_WRITE_S_COIL, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(MODBUS_COIL_ON, read_u16_from_buff(outputBuffer+3));
}

TEST_F(ModbusTest, writeSingleCoilOFF)
{
    uint16_t addr = 0x01;
    
    modbus_master_write_s_coil(addr, MODBUS_COIL_OFF, outputBuffer);

    ASSERT_EQ(MODBUS_FC_WRITE_S_COIL, outputBuffer[0]);
    ASSERT_EQ(addr, read_u16_from_buff(outputBuffer+1));
    ASSERT_EQ(MODBUS_COIL_OFF, read_u16_from_buff(outputBuffer+3));
}

}
