#ifndef CC1101_TYPES_H
#define CC1101_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef enum
{   
    CC1101_ERROR = -10,

    CC1101_OK = 0,
}cc1101_err_t;


typedef enum
{
    CC1101_REG_IOCFG2 = 0,
}cc1101_reg_t;

typedef union //cc1101_status_byte_u
{
    struct //cc1101_status_byte_s
    {
        uint8_t		FIFO_BYTES_AVAILABLE			:4;
        uint8_t		STATE			:3;
        uint8_t		CHIP_RDYn			:1;
    }fields;
    uint8_t data;
}cc1101_status_byte_t;



typedef void (*cc1101_spi_read_p)(uint8_t * data);
typedef void (*cc1101_spi_write_p)(uint8_t data);
typedef void (*cc1101_delay_ms_p)(uint32_t delay_ms);


typedef struct
{
    cc1101_spi_read_p        spi_read_byte;
    cc1101_spi_write_p        spi_write_byte;
    cc1101_delay_ms_p               delay_ms;

}cc1101_handle_t;


#endif /* CC1101_TYPES_H */
