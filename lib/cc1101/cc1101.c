#include "cc1101.h"

cc1101_handle_t _cc1101_handle;
cc1101_registers_definitions_t _cc1101_registers_def;
cc1101_status_byte_t cc1101_status;

extern cc1101_err_t cc1101_write_reg(cc1101_reg_idx_t reg_idx, size_t len, uint8_t * data);
extern cc1101_err_t cc1101_read_reg(cc1101_reg_idx_t reg_idx, size_t len, uint8_t * data);
extern void spi_read_bytes(uint8_t * data_out, size_t len);
extern void spi_write_bytes(uint8_t * data_in, size_t len);


cc1101_err_t cc1101_init(cc1101_spi_read_p spi_read_byte, cc1101_spi_write_p spi_write_byte, cc1101_delay_ms_p delay_ms,  
                            cc1101_cs_enable_disable_p cs_enable, cc1101_cs_enable_disable_p  cs_disable, cc1101_read_miso_p read_miso)
{
    
    LOG_DEBUG("Inside cc1101 init\n");
    _cc1101_handle.delay_ms = delay_ms;
    _cc1101_handle.spi_read_byte = spi_read_byte;
    _cc1101_handle.spi_write_byte = spi_write_byte;
    _cc1101_handle.spi_read_bytes = spi_read_bytes;
    _cc1101_handle.spi_write_bytes = spi_write_bytes;
    _cc1101_handle.cs_enable = cs_enable;
    _cc1101_handle.cs_disable = cs_disable;
    _cc1101_handle.read_miso = read_miso;

    return CC1101_OK;
}


cc1101_handle_t * cc1101_get_handle(void)
{
    return &_cc1101_handle;
}

cc1101_registers_definitions_t * cc1101_get_registers_definition(void)
{
    return &_cc1101_registers_def;
}


cc1101_err_t read_test(void)
{
    cc1101_err_t ret = CC1101_ERROR;

    uint8_t iocfg2 = 0;

    ret = cc1101_read_reg(CC1101_REG_FIFOTHR, 1, &iocfg2);

    LOG_DEBUG("Ret: %d\n", ret);

    LOG_DEBUG("Status: 0x%02hx\n", cc1101_status.data);

    LOG_DEBUG("IOCFG2 Value: 0x%02hx\n", iocfg2);

    return ret;
}


