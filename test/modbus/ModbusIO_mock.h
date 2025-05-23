#include "gmock/gmock.h"

extern "C"
{
    #include "ModbusIO.h"
}

class ModbusIOMock {
public:
    MOCK_METHOD(uint16_t, hreg_get, (uint16_t addr));
    MOCK_METHOD(uint16_t, coil_get, (uint16_t addr));
    MOCK_METHOD(uint16_t, digitalIn_get, (uint16_t addr));
    MOCK_METHOD(uint16_t, inreg_get, (uint16_t addr));
};

void modbus_io_mock_init(ModbusIOMock *mock);