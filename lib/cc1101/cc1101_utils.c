#include "cc1101_reg.h"
#include "cc1101_types.h"

extern cc1101_handle_t _cc1101_handle;
extern cc1101_registers_definitions_t _cc1101_registers_def;
extern cc1101_status_byte_t cc1101_status;


cc1101_err_t cc1101_write_reg(cc1101_reg_idx_t reg_idx, size_t len, uint8_t * data);
cc1101_err_t cc1101_read_reg(cc1101_reg_idx_t reg_idx, size_t len, uint8_t * data);
void spi_read_bytes(uint8_t * data_out, size_t len);
void spi_write_bytes(uint8_t * data_in, size_t len);
cc1101_err_t wait_for_miso(void);


cc1101_err_t cc1101_write_reg(cc1101_reg_idx_t reg_idx, size_t len, uint8_t * data)
{
    cc1101_err_t ret = CC1101_ERROR;

    // Register Index is out of bounds
    if((reg_idx <= _CC1101_FIRST_ELEMENT) || (reg_idx >= _CC1101_LAST_ELEMENT)) return CC1101_ERROR;

    cc1101_trans_reg_t trans_reg = translation_regs[reg_idx];

    // Register access is only READ ONLY
    if(trans_reg.reg_access_type == CC1101_REG_ACCESS_TYPE_READ_ONLY || trans_reg.reg_access_type == CC1101_REG_ACCESS_TYPE_UNKNOWN) return CC1101_ERROR;

    _cc1101_handle.cs_enable();

    ret = wait_for_miso();

    if(ret != CC1101_OK)
    {
        _cc1101_handle.cs_disable();
        return ret;
    }

    switch (trans_reg.reg_type)
    {

        case CC1101_REG_TYPE_CONFIG:
            if(len > 1)
            {
                /* Write Multiple(Burst) bytes to Register address */
                _cc1101_handle.spi_write_byte((CC1101_REGISTER_WRITE_BIT | CC1101_REGISTER_BURST_ACCESS | trans_reg.reg_addr));
                _cc1101_handle.spi_write_bytes(data, len);
            }
            else
            {
                /* Write single byte to register address */
                _cc1101_handle.spi_write_byte((CC1101_REGISTER_WRITE_BIT | CC1101_REGISTER_SINGLE_ACCESS | trans_reg.reg_addr));
                _cc1101_handle.spi_write_byte(*data);
            }
            break;

        case CC1101_REG_TYPE_STROBE_CMD:
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_WRITE_BIT | CC1101_REGISTER_SINGLE_ACCESS | trans_reg.reg_addr));
            break;

        case CC1101_REG_TYPE_FIFO:
            if(len > 1)
            {
                /* Write Multiple(Burst) bytes to Register address */
                _cc1101_handle.spi_write_byte((CC1101_REGISTER_WRITE_BIT | CC1101_REGISTER_BURST_ACCESS | trans_reg.reg_addr));
                _cc1101_handle.spi_write_bytes(data, len);
            }
            else
            {
                /* Write single byte to register address */
                _cc1101_handle.spi_write_byte((CC1101_REGISTER_WRITE_BIT | CC1101_REGISTER_SINGLE_ACCESS | trans_reg.reg_addr));
                _cc1101_handle.spi_write_byte(*data);
            }
            break;

        case CC1101_REG_TYPE_PATABLE:
            if(len > 1)
            {
                /* Write Multiple(Burst) bytes to Register address */
                _cc1101_handle.spi_write_byte((CC1101_REGISTER_WRITE_BIT | CC1101_REGISTER_BURST_ACCESS | trans_reg.reg_addr));
                _cc1101_handle.spi_write_bytes(data, len);
            }
            else
            {
                /* Write single byte to register address */
                _cc1101_handle.spi_write_byte((CC1101_REGISTER_WRITE_BIT | CC1101_REGISTER_SINGLE_ACCESS | trans_reg.reg_addr));
                _cc1101_handle.spi_write_byte(*data);
            }
            break;

        case CC1101_REG_TYPE_MARKER:
        case CC1101_REG_TYPE_STATUS:
            _cc1101_handle.cs_disable();
            return CC1101_ERROR;
            break;
        
        default:
            _cc1101_handle.cs_disable();
            return CC1101_ERROR;
            break;
    }


    _cc1101_handle.cs_disable();
    return ret;
}

cc1101_err_t cc1101_read_reg(cc1101_reg_idx_t reg_idx, size_t len, uint8_t * data)
{
    cc1101_err_t ret = CC1101_ERROR;

    // Register Index is out of bounds
    if((reg_idx <= _CC1101_FIRST_ELEMENT) || (reg_idx >= _CC1101_LAST_ELEMENT)) return CC1101_ERROR;

    cc1101_trans_reg_t trans_reg = translation_regs[reg_idx];

    // Register access is only WRITE ONLY or Unknown
    if(trans_reg.reg_access_type == CC1101_REG_ACCESS_TYPE_UNKNOWN || trans_reg.reg_access_type == CC1101_REG_ACCESS_TYPE_WRITE_ONLY) return CC1101_ERROR;

    _cc1101_handle.cs_enable();

    ret = wait_for_miso();

    if(ret != CC1101_OK)
    {
        _cc1101_handle.cs_disable();
        return ret;
    }

    switch (trans_reg.reg_type)
    {
    case CC1101_REG_TYPE_CONFIG:
        if(len > 1)
        {
            // Multiple Bytes Read (Burst)
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_BURST_ACCESS | trans_reg.reg_addr);
            _cc1101_handle.spi_read_byte(&cc1101_status.data);
            _cc1101_handle.spi_read_bytes(data, len);
        }
        else
        {
            // Single Byte Read
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_SINGLE_ACCESS | trans_reg.reg_addr);
            _cc1101_handle.spi_read_byte(&cc1101_status.data);
            _cc1101_handle.spi_read_byte(data);
        }
        break;
    case CC1101_REG_TYPE_STATUS:
        if(len > 1)
        {
            // Multiple Bytes Read (Burst)
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_BURST_ACCESS | trans_reg.reg_addr);
            _cc1101_handle.spi_read_byte(&cc1101_status.data);
            _cc1101_handle.spi_read_bytes(data, len);
        }
        else
        {
            // Single Byte Read
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_BURST_ACCESS | trans_reg.reg_addr);
            _cc1101_handle.spi_read_byte(&cc1101_status.data);
            _cc1101_handle.spi_read_byte(data);
        }
        break;
    case CC1101_REG_TYPE_STROBE_CMD:
        // Single Byte Read
        _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_SINGLE_ACCESS | trans_reg.reg_addr);
        // _cc1101_handle.spi_read_byte(&cc1101_status.data);
        // _cc1101_handle.spi_read_byte(data);
        break;
    case CC1101_REG_TYPE_FIFO:
        if(len > 1)
        {
            // Multiple Bytes Read (Burst)
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_BURST_ACCESS | trans_reg.reg_addr);
            _cc1101_handle.spi_read_byte(&cc1101_status.data);
            _cc1101_handle.spi_read_bytes(data, len);
        }
        else
        {
            // Single Byte Read
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_SINGLE_ACCESS | trans_reg.reg_addr);
            _cc1101_handle.spi_read_byte(&cc1101_status.data);
            _cc1101_handle.spi_read_byte(data);
        }
        break;
    case CC1101_REG_TYPE_PATABLE:
        if(len > 1)
        {
            // Multiple Bytes Read (Burst)
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_BURST_ACCESS | trans_reg.reg_addr);
            _cc1101_handle.spi_read_byte(&cc1101_status.data);
            _cc1101_handle.spi_read_bytes(data, len);
        }
        else
        {
            // Single Byte Read
            _cc1101_handle.spi_write_byte((CC1101_REGISTER_READ_BIT) | CC1101_REGISTER_SINGLE_ACCESS | trans_reg.reg_addr);
            _cc1101_handle.spi_read_byte(&cc1101_status.data);
            _cc1101_handle.spi_read_byte(data);
        }
        break;
    
    case CC1101_REG_TYPE_MARKER:
    default:
        _cc1101_handle.cs_disable();
        return CC1101_ERROR;
        break;
    }


    _cc1101_handle.cs_disable();
    return ret;
}

void spi_read_bytes(uint8_t * data_out, size_t len)
{
    uint8_t counter = 0;
    for(counter = 0; counter < len; counter++)
    {
        _cc1101_handle.spi_read_byte(&data_out[counter]);
    }
}

void spi_write_bytes(uint8_t * data_in, size_t len)
{
    uint8_t counter = 0;
    for(counter = 0; counter < len; counter++)
    {
        _cc1101_handle.spi_write_byte(data_in[counter]);
    }
}

cc1101_err_t wait_for_miso(void)
{
    uint8_t time_passed = 0;
    while(_cc1101_handle.read_miso() == 1)
    {
        // If more than 200ms passed and MISO has not gone LOW, return error;
        if(time_passed > 200) return CC1101_ERROR_MISO_NOT_LOW;
        time_passed++;
        _cc1101_handle.delay_ms(1);
    }

    return CC1101_OK;
}