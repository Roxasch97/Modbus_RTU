#include "gtest/gtest.h"
#include "ModbusRtu.h"
#include "ModbusUtils.h"
#include "ModbusIO_mock.h"

using ::testing::Return; 
namespace {

class ModbusResponsesTest : public testing::Test
{
    protected:

    void SetUp() override
    {
        memset(requestBuffer, 0, sizeof(uint8_t)*MODBUS_BUF_LEN);
        memset(responseBuffer, 0, sizeof(uint8_t)*MODBUS_BUF_LEN);
    }

    void TearDown() override
    {

    }
    uint8_t requestBuffer[MODBUS_BUF_LEN] = {0};
    uint8_t responseBuffer[MODBUS_BUF_LEN] = {0};
};

TEST_F(ModbusResponsesTest, readHregTest_single)
{
    uint16_t addr = 0x0006;
    uint16_t len = 1;

    ModbusIOMock mock;

    EXPECT_CALL(mock, hreg_get(addr))
        .Times(1)
        .WillOnce(Return(0x01));

    modbus_io_mock_init(&mock);

    modbus_master_read_hreg(addr, len, requestBuffer);
    modbus_slave_read_hreg_resp(requestBuffer, responseBuffer);

    ASSERT_EQ(MODBUS_FC_READ_HOLD_REG, responseBuffer[0]);
    ASSERT_EQ(len*2, responseBuffer[1]);
    ASSERT_EQ(read_u16_from_buff(responseBuffer+2), 0x01);

    for(int i = 4; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(responseBuffer[i], 0);
    }


}

TEST_F(ModbusResponsesTest, readHregTest_multiple)
{
    uint16_t addr = 0x0006;
    uint16_t len = 3;

    ModbusIOMock mock;

    EXPECT_CALL(mock, hreg_get(addr))
        .WillOnce(Return(0xFFFF));
    EXPECT_CALL(mock, hreg_get(addr+1))
        .WillOnce(Return(0x02));
    EXPECT_CALL(mock, hreg_get(addr+2))
        .WillOnce(Return(0xF0));

    modbus_io_mock_init(&mock);

    modbus_master_read_hreg(addr, len, requestBuffer);
    modbus_slave_read_hreg_resp(requestBuffer, responseBuffer);

    ASSERT_EQ(MODBUS_FC_READ_HOLD_REG, responseBuffer[0]);
    ASSERT_EQ(len*2, responseBuffer[1]);
    ASSERT_EQ(read_u16_from_buff(responseBuffer+2), 0xFFFF);
    ASSERT_EQ(read_u16_from_buff(responseBuffer+4), 0x02);
    ASSERT_EQ(read_u16_from_buff(responseBuffer+6), 0xF0);

    for(int i = 8; i<MODBUS_BUF_LEN; i++)
    {
    ASSERT_EQ(responseBuffer[i], 0);
    }
}

TEST_F(ModbusResponsesTest, readCoilsTest_single)
{
    uint16_t addr = 0x0006;
    uint16_t len = 1;
    uint8_t byteCount = 1;
    ModbusIOMock mock;

    EXPECT_CALL(mock, coil_get(addr))
        .Times(1)
        .WillOnce(Return(0x01));

    modbus_io_mock_init(&mock);

    modbus_master_read_coils(addr, len, requestBuffer);
    modbus_slave_read_coils_resp(requestBuffer, responseBuffer);

    ASSERT_EQ(MODBUS_FC_READ_COILS, responseBuffer[0]);
    ASSERT_EQ(byteCount, responseBuffer[1]);
    ASSERT_EQ(responseBuffer[2], 0x01);
}

TEST_F(ModbusResponsesTest, readCoilsTest_multiple_one_byte)
{
    uint16_t addr = 0x0006;
    uint16_t len = 8;
    uint8_t byteCount = 1;
    ModbusIOMock mock;

    for (uint16_t i = 0; i < len; i++) {
        EXPECT_CALL(mock, coil_get(addr + i))
            .Times(1)
            .WillOnce(Return(0x01)); // Example return value
    }
        
    modbus_io_mock_init(&mock);

    modbus_master_read_coils(addr, len, requestBuffer);
    modbus_slave_read_coils_resp(requestBuffer, responseBuffer);

    ASSERT_EQ(MODBUS_FC_READ_COILS, responseBuffer[0]);
    ASSERT_EQ(byteCount, responseBuffer[1]);
    ASSERT_EQ(responseBuffer[2], 0xFF);
}

TEST_F(ModbusResponsesTest, readCoilsTest_multiple_more_bytes){
    uint16_t addr = 0x0006;
    uint16_t len = 10;
    uint8_t byteCount = 2;
    ModbusIOMock mock;

    for (uint16_t i = 0; i < len; i++) {
        EXPECT_CALL(mock, coil_get(addr + i))
            .Times(1)
            .WillOnce(Return(0x01)); // Example return value
    }
        
    modbus_io_mock_init(&mock);

    modbus_master_read_coils(addr, len, requestBuffer);
    modbus_slave_read_coils_resp(requestBuffer, responseBuffer);

    ASSERT_EQ(MODBUS_FC_READ_COILS, responseBuffer[0]);
    ASSERT_EQ(byteCount, responseBuffer[1]);
    ASSERT_EQ(responseBuffer[2], 0xFF);
    ASSERT_EQ(responseBuffer[3], 0x03);
}

TEST_F(ModbusResponsesTest, readDinTest_single)
{
    uint16_t addr = 0x0002;
    uint16_t len = 1;
    uint8_t byteCount = 1;
    ModbusIOMock mock;

    EXPECT_CALL(mock, digitalIn_get(addr))
        .Times(1)
        .WillOnce(Return(0x01));

    modbus_io_mock_init(&mock);

    modbus_master_read_discrete_in(addr, len, requestBuffer);
    modbus_slave_read_discrete_in_resp(requestBuffer, responseBuffer);

    ASSERT_EQ(MODBUS_FC_READ_DISCRETE_IN, responseBuffer[0]);
    ASSERT_EQ(byteCount, responseBuffer[1]);
    ASSERT_EQ(responseBuffer[2], 0x01);
}

TEST_F(ModbusResponsesTest, readDinTest_multiple_one_byte)
{
    uint16_t addr = 0x0002;
    uint16_t len = 8;
    uint8_t byteCount = 1;
    ModbusIOMock mock;

    for (uint16_t i = 0; i < len; i++) {
        EXPECT_CALL(mock, digitalIn_get(addr + i))
            .Times(1)
            .WillOnce(Return(0x01));
    }
        
    modbus_io_mock_init(&mock);

    modbus_master_read_discrete_in(addr, len, requestBuffer);
    modbus_slave_read_discrete_in_resp(requestBuffer, responseBuffer);

    ASSERT_EQ(MODBUS_FC_READ_DISCRETE_IN, responseBuffer[0]);
    ASSERT_EQ(byteCount, responseBuffer[1]);
    ASSERT_EQ(responseBuffer[2], 0xFF);
}

TEST_F(ModbusResponsesTest, readDinTest_multiple_more_bytes)
{
    uint16_t addr = 0x0002;
    uint16_t len = 10;
    uint8_t byteCount = 2;
    ModbusIOMock mock;

    for (uint16_t i = 0; i < len; i++) {
        EXPECT_CALL(mock, digitalIn_get(addr + i))
            .Times(1)
            .WillOnce(Return(0x01));
    }
        
    modbus_io_mock_init(&mock);

    modbus_master_read_discrete_in(addr, len, requestBuffer);
    modbus_slave_read_discrete_in_resp(requestBuffer, responseBuffer);

    ASSERT_EQ(MODBUS_FC_READ_DISCRETE_IN, responseBuffer[0]);
    ASSERT_EQ(byteCount, responseBuffer[1]);
    ASSERT_EQ(responseBuffer[2], 0xFF);
    ASSERT_EQ(responseBuffer[3], 0x03);
}
