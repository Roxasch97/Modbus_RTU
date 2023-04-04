#include "gtest/gtest.h"
#include "ModbusRtu.h"

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
    ModbusAddrType addr = 0x01;
    ModbusLenType len = 1;

    modbus_master_read_hreg(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_HOLD_REG, outputBuffer[0]);
    ASSERT_EQ(addr, outputBuffer[1] << 8 | outputBuffer[2]);
    ASSERT_EQ(len, outputBuffer[3] << 8 | outputBuffer[4]);
}

TEST_F(ModbusTest, readCoilsTest)
{
    ModbusAddrType addr = 0x01;
    ModbusLenType len = 1;

    modbus_master_read_coils(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_COILS, outputBuffer[0]);
    ASSERT_EQ(addr, outputBuffer[1] << 8 | outputBuffer[2]);
    ASSERT_EQ(len, outputBuffer[3] << 8 | outputBuffer[4]);
}

TEST_F(ModbusTest, readDiscreteIn)
{
    ModbusAddrType addr = 0x01;
    ModbusLenType len = 1;

    modbus_master_read_discrete_in(addr,len,outputBuffer);

    ASSERT_EQ(MODBUS_FC_READ_DISCRETE_IN, outputBuffer[0]);
    ASSERT_EQ(addr, outputBuffer[1] << 8 | outputBuffer[2]);
    ASSERT_EQ(len, outputBuffer[3] << 8 | outputBuffer[4]);
}
}
