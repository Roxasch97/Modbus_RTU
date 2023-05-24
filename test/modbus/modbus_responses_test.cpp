#include "gtest/gtest.h"
#include "ModbusRtu.h"
#include "ModbusUtils.h"

using testing::Test;

namespace {

class ModbusResponsesTest : public testing::Test
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

TEST_F(ModbusResponsesTest, readHregTest)
{
    FAIL()<< "Environment testing fail :)";
}

}
