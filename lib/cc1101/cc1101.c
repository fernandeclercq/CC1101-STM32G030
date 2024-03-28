#include "cc1101.h"

cc1101_handle_t * _cc1101_handle;

cc1101_err_t cc1101_write_reg(cc1101_reg_t reg_idx, size_t len, uint8_t * data);
cc1101_err_t cc1101_read_reg(cc1101_reg_t reg_idx, size_t len, uint8_t * data);

cc1101_err_t cc1101_init(cc1101_handle_t * handle)
{
    _cc1101_handle = handle;

    return CC1101_OK;
}


cc1101_err_t cc1101_write_reg(cc1101_reg_t reg_idx, size_t len, uint8_t * data)
{
    cc1101_err_t ret = CC1101_ERROR;



    return ret;
}


cc1101_err_t cc1101_read_reg(cc1101_reg_t reg_idx, size_t len, uint8_t * data)
{
    cc1101_err_t ret = CC1101_ERROR;



    return ret;
}