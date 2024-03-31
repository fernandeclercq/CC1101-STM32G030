#ifndef CC1101_H
#define CC1101_H

#include "cc1101_reg.h"
#include "cc1101_types.h"


/**
 * @brief 
 * 
 * @param spi_read_byte 
 * @param spi_write_byte 
 * @param delay_ms 
 * @param cs_enable 
 * @param cs_disable 
 * @param wait_miso 
 * @return cc1101_err_t 
 */
cc1101_err_t cc1101_init(cc1101_spi_read_p spi_read_byte, cc1101_spi_write_p spi_write_byte, cc1101_delay_ms_p delay_ms,  
                            cc1101_cs_enable_disable_p cs_enable, cc1101_cs_enable_disable_p  cs_disable, cc1101_read_miso_p read_miso);


cc1101_handle_t * cc1101_get_handle(void);
cc1101_registers_definitions_t * cc1101_get_registers_definition(void);
cc1101_err_t read_test(void);

#endif /* CC1101_H */
