#include "ModbusIO_mock.h"

static ModbusIOMock *_mock = nullptr;

void modbus_io_mock_init(ModbusIOMock *mock)
{
    _mock = mock;
}

extern "C"
{


    uint16_t hreg_get(uint16_t hregAddr)
    {
        return _mock->hreg_get(hregAddr);
    }

    uint16_t coil_get(uint16_t coilAddr)
    {
        return _mock->coil_get(coilAddr);
    }

    uint16_t digitalIn_get(uint16_t dinAddr)
    {
        return _mock->digitalIn_get(dinAddr);
    }
}