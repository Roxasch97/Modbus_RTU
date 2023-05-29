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

}