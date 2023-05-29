#include "gmock/gmock.h"

extern "C"
{
    #include "ModbusIO.h"
}

class ModbusIOMock {
public:
    MOCK_METHOD(uint16_t, hreg_get, (uint16_t addr));
};

void modbus_io_mock_init(ModbusIOMock *mock);