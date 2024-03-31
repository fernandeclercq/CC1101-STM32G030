#ifndef CC1101_TYPES_H
#define CC1101_TYPES_H

#include <stdint.h>
#include <stddef.h>
#include "cc1101_reg.h"

typedef enum
{   
    CC1101_ERROR = -20,
    CC1101_ERROR_MISO_NOT_LOW,

    CC1101_OK = 0,
}cc1101_err_t;


typedef enum
{
    CC1101_REG_TYPE_CONFIG = 0x00U,
    CC1101_REG_TYPE_STATUS,
    CC1101_REG_TYPE_STROBE_CMD,
    CC1101_REG_TYPE_FIFO,
    CC1101_REG_TYPE_PATABLE,
    CC1101_REG_TYPE_MARKER,
}cc1101_reg_type_t;

typedef enum
{
    CC1101_REG_ACCESS_TYPE_UNKNOWN = 0x00U,
    CC1101_REG_ACCESS_TYPE_READ_ONLY,
    CC1101_REG_ACCESS_TYPE_WRITE_ONLY,
    CC1101_REG_ACCESS_TYPE_READ_WRITE,
    CC1101_REG_ACCESS_TYPE_READ_MOD_WRITE,
}cc1101_reg_access_type_t;


typedef struct
{
    void            *           reg_struct;
    uint8_t                     reg_addr;
    cc1101_reg_type_t           reg_type;
    cc1101_reg_access_type_t    reg_access_type;
}cc1101_trans_reg_t;


typedef enum
{
    _CC1101_FIRST_ELEMENT,

    CC1101_REG_IOCFG2,
    CC1101_REG_IOCFG1,
    CC1101_REG_IOCFG0,

    CC1101_REG_FIFOTHR,

    CC1101_REG_SYNC1,
    CC1101_REG_SYNC0,
    CC1101_REG_PKTLEN,

    CC1101_REG_PKTCTRL1,
    CC1101_REG_PKTCTRL0,

    CC1101_REG_ADDR,
    CC1101_REG_CHANNR,

    CC1101_REG_FSCTRL1,

    CC1101_REG_FSCTRL0,

    CC1101_REG_FREQ2,

    CC1101_REG_FREQ1,
    CC1101_REG_FREQ0,
    CC1101_REG_MDMCFG4,
    CC1101_REG_MDMCFG3,
    CC1101_REG_MDMCFG2,

    CC1101_REG_MDMCFG1,

    CC1101_REG_MDMCFG0,

    CC1101_REG_DEVIATN,

    CC1101_REG_MCSM2,

    CC1101_REG_MCSM1,

    CC1101_REG_MCSM0,

    CC1101_REG_FOCCFG,

    CC1101_REG_BSCFG,
    CC1101_REG_AGCCTRL2,

    CC1101_REG_AGCCTRL1,

    CC1101_REG_AGCCTRL0,
    CC1101_REG_WOREVT1,
    CC1101_REG_WOREVT0,

    CC1101_REG_WORCTRL,

    CC1101_REG_FREND1,

    CC1101_REG_FREND0,

    CC1101_REG_FSCAL3,

    CC1101_REG_FSCAL2,

    CC1101_REG_FSCAL1,
    
    CC1101_REG_FSCAL0,

    CC1101_REG_RCCTRL1,

    CC1101_REG_RCCTRL0,

    CC1101_REG_FSTEST,
    CC1101_REG_PTEST,
    CC1101_REG_AGCTEST,
    CC1101_REG_TEST2,
    CC1101_REG_TEST1,
    CC1101_REG_TEST0,

    /**************************** Strobe Commands ******************************/
    CC1101_REG_SRES,
    CC1101_REG_SFSTXON,
    CC1101_REG_SXOFF,
    CC1101_REG_SCAL,
    CC1101_REG_SRX,
    CC1101_REG_STX,
    CC1101_REG_SIDLE,
    CC1101_REG_SWOR,
    CC1101_REG_SPWD,
    CC1101_REG_SFRX,
    CC1101_REG_SFTX,
    CC1101_REG_SWORRST,
    CC1101_REG_SNOP,
    /************************************************************************/
    CC1101_REG_PATABLE,
    /************************** TX FIFO - Write Only ************************/
    CC1101_REG_TXFIFO,
    /************************** RX FIFO - Read Only ************************/
    CC1101_REG_RXFIFO,
    /**************************** Status Registers ******************************/
    CC1101_REG_PARTNUM,
    CC1101_REG_VERSION,
    CC1101_REG_FREQEST,
    CC1101_REG_LQI,
    CC1101_REG_RSSI,
    CC1101_REG_MARCSTATE,
    CC1101_REG_WORTIME1,
    CC1101_REG_WORTIME0,
    CC1101_REG_PKTSTATUS,
    CC1101_REG_VCO_VC_DAC,
    CC1101_REG_TXBYTES,
    CC1101_REG_RXBYTES,
    CC1101_REG_RCCTRL1_STATUS,
    CC1101_REG_RCCTRL0_STATUS,
    /************************************************************************/

    _CC1101_LAST_ELEMENT,
}cc1101_reg_idx_t;

extern const cc1101_trans_reg_t translation_regs[];


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


/**************************************************************************/


typedef void (*cc1101_spi_read_p)(uint8_t * data);
typedef void (*cc1101_spi_write_p)(uint8_t data);
typedef void (*cc1101_spi_read_bytes_p)(uint8_t * data, size_t len);
typedef void (*cc1101_spi_write_bytes_p)(uint8_t * data, size_t len);
typedef void (*cc1101_delay_ms_p)(uint32_t delay_ms);
typedef void (*cc1101_cs_enable_disable_p)(void);
typedef uint8_t (*cc1101_read_miso_p)(void);


typedef struct
{
    /**
     * @brief SPI Read Byte | Signature: (uint8_t * data)
     * @param[out] data Pointer to the byte;
     */
    cc1101_spi_read_p        spi_read_byte;
    /**
     * @brief SPI Write Byte | Signature: (uint8_t data)
     * @param[in] data Single byte of type uint8_t
     */
    cc1101_spi_write_p        spi_write_byte;

    /**
     * @brief SPI Multiple Byte Read | Signature: (uint8_t * data, size_t len);
     * @param[out] data A pointer to the receive buffer.
     * @param[in] len A value representing the length of bytes to read.
     */
    cc1101_spi_read_bytes_p     spi_read_bytes;

    /**
     * @brief SPI Multiple Byte Write | Signature: (uint8_t * data, size_t len);
     * @param[in] data A pointer to the transmit buffer.
     * @param[in] len A value representing the length of bytes to write.
     */
    cc1101_spi_write_bytes_p    spi_write_bytes;

    /**
     * @brief Delay milliseconds(blocking)
     * @param[in] delay_ms A Value for the delay in milliseconds
     */
    cc1101_delay_ms_p               delay_ms;

    /**
     * @brief Enables the Chip Select Line (Pulls the CS Line LOW)
     * 
     */
    cc1101_cs_enable_disable_p      cs_enable;

    /**
     * @brief Disables the Chip Select Line (Pulls the CS Line HIGH)
     * 
     */
    cc1101_cs_enable_disable_p      cs_disable;

    /**
     * @brief Read the MISO gpio
     * 
     */
    cc1101_read_miso_p              read_miso;

}cc1101_handle_t;

/**************************************************************************/


#endif /* CC1101_TYPES_H */
