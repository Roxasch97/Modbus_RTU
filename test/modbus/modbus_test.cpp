#include "gtest/gtest.h"
#include "ModbusRtu.h"

using testing::Test;

namespace {

class ModbusTest : public testing::Test
{
    protected:

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }

};

TEST(ModbusTest, FirstTest)
{
    ModbusAddrType addr = 0x01;
    ModbusLenType len = 1;

    modbusMasterReadHreg(addr,len);

    FAIL() << "Implement your test!";
}

}
