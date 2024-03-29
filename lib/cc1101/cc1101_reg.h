#ifndef CC1101_REG_H
#define CC1101_REG_H


#define REGISTER_SINGLE_ACCESS 0x00
#define REGISTER_BURST_ACCESS 0x40

#define REGISTER_READ_BIT 0x80
#define REGISTER_WRITE_BIT 0x00


typedef enum
{
    CC1101_CONFIG_REG_IOCFG2 = 0x00,    // 0x00
    CC1101_CONFIG_REG_IOCFG1,           // 0x01
    CC1101_CONFIG_REG_IOCFG0,           // 0x02
    CC1101_CONFIG_REG_FIFOTHR,          // 0x03
    CC1101_CONFIG_REG_SYNC1,            // 0x04
    CC1101_CONFIG_REG_SYNC0,            // 0x05
    CC1101_CONFIG_REG_PKTLEN,           // 0x06
    CC1101_CONFIG_REG_PKTCTRL1,         // 0x07
    CC1101_CONFIG_REG_PKTCTRL0,         // 0x08
    CC1101_CONFIG_REG_ADDR,             // 0x09
    CC1101_CONFIG_REG_CHANNR,           // 0x0A
    CC1101_CONFIG_REG_FSCTRL1,          // 0x0B
    CC1101_CONFIG_REG_FSCTRL0,          // 0x0C
    CC1101_CONFIG_REG_FREQ2,            // 0x0D
    CC1101_CONFIG_REG_FREQ1,            // 0x0E
    CC1101_CONFIG_REG_FREQ0,            // 0x0F
    CC1101_CONFIG_REG_MDMCFG4,          // 0x10
    CC1101_CONFIG_REG_MDMCFG3,          // 0x11
    CC1101_CONFIG_REG_MDMCFG2,          // 0x12
    CC1101_CONFIG_REG_MDMCFG1,          // 0x13
    CC1101_CONFIG_REG_MDMCFG0,          // 0x14
    CC1101_CONFIG_REG_DEVIATN,          // 0x15
    CC1101_CONFIG_REG_MCSM2,            // 0x16
    CC1101_CONFIG_REG_MCSM1,            // 0x17
    CC1101_CONFIG_REG_MCSM0,            // 0x18
    CC1101_CONFIG_REG_FOCCFG,           // 0x19
    CC1101_CONFIG_REG_BSCFG,            // 0x1A
    CC1101_CONFIG_REG_AGCCTRL2,         // 0x1B
    CC1101_CONFIG_REG_AGCCTRL1,         // 0x1C
    CC1101_CONFIG_REG_AGCCTRL0,         // 0x1D
    CC1101_CONFIG_REG_WOREVT1,          // 0x1E
    CC1101_CONFIG_REG_WOREVT0,          // 0x1F
    CC1101_CONFIG_REG_WORCTRL,          // 0x20
    CC1101_CONFIG_REG_FREND1,           // 0x21
    CC1101_CONFIG_REG_FREND0,           // 0x22
    CC1101_CONFIG_REG_FSCAL3,           // 0x23
    CC1101_CONFIG_REG_FSCAL2,           // 0x24
    CC1101_CONFIG_REG_FSCAL1,           // 0x25
    CC1101_CONFIG_REG_FSCAL0,           // 0x26
    CC1101_CONFIG_REG_RCCTRL1,          // 0x27
    CC1101_CONFIG_REG_RCCTRL0,          // 0x28
    CC1101_CONFIG_REG_FSTEST,           // 0x29
    CC1101_CONFIG_REG_PTEST,            // 0x2A
    CC1101_CONFIG_REG_AGCTEST,          // 0x2B
    CC1101_CONFIG_REG_TEST2,            // 0x2C
    CC1101_CONFIG_REG_TEST1,            // 0x2D
    CC1101_CONFIG_REG_TEST0,            // 0x2E
}cc1101_reg_address_t;




typedef enum
{
    /* Asserts when RX FIFO is filled at or above the RX FIFO threshold. De-asserts when RX FIFO is drained below the same threshold.*/
    CC1101_GDOx_CFG_RX_FIFO_THRESHOLD = 0,
    /* Asserts when RX FIFO is filled at or above the RX FIFO threshold or the end of packet is reached. De-asserts when the RX FIFO is empty.*/
    CC1101_GDOx_CFG_RX_END_PACKET,
    /* Asserts when the TX FIFO is filled at or above the TX FIFO threshold. De-asserts when the TX FIFO is below the same threshold.*/
    CC1101_GDOx_CFG_TX_FIFO_THRESHOLD,
    /* Asserts when TX FIFO is full. De-asserts when the TX FIFO is drained below the TX FIFO threshold.*/
    CC1101_GDOx_CFG_TX_FIFO_FULL,
    /* Asserts when the RX FIFO has overflowed. De-asserts when the FIFO has been flushed. */
    CC1101_GDOx_CFG_RX_FIFO_OVERFLOW,
    /* Asserts when the TX FIFO has underflowed. De-asserts when the FIFO is flushed. */
    CC1101_GDOx_CFG_TX_FIFO_UNDERFLOW,
    /* Asserts when sync word has been sent / received, and de-asserts at the end of the packet. 
        In RX, the pin will also de-assert when a packet is discarded due to address or maximum length filtering or when the radio enters
        RXFIFO_OVERFLOW state. In TX the pin will de-assert if the TX FIFO underflows. */
    CC1101_GDOx_CFG_RX_TX_SYNC,
    
    /* Asserts when a packet has been received with CRC OK. De-asserts when the first byte is read from the RX FIFO */
    CC1101_GDOx_CFG_CRC_OK,
    /* Preamble Quality Reached. Asserts when the PQI is above the programmed PQT value. 
        De-asserted when the chip re-enters RX state (MARCSTATE=0x0D) or the PQI gets below the programmed PQT value. */
    CC1101_GDOx_CFG_PREAMBLE_QUALITY_REACHED,
    /* Clear channel assessment. High when RSSI level is below threshold (dependent on the current CCA_MODE setting) */
    CC1101_GDOx_CFG_CHANNEL_CLEAR,
    /* Lock detector output. The PLL is in lock if the lock detector output has a positive transition or is constantly logic high. 
        To check for PLL lock the lock detector output should be used as an interrupt for the MCU. */
    CC1101_GDOx_CFG_PLL_LOCK,
    /* Serial Clock. Synchronous to the data in synchronous serial mode.
        In RX mode, data is set up on the falling edge by CC1101 when GDOx_INV=0.
        In TX mode, data is sampled by CC1101 on the rising edge of the serial clock when GDOx_INV=0. */
    CC1101_GDOx_CFG_SERIAL_TX_RX_CLOCK,
    /* Serial Synchronous Data Output. Used for synchronous serial mode. */
    CC1101_GDOx_CFG_SERIAL_SYNC_DATA_OUT,
    /* Serial Data Output. Used for asynchronous serial mode. */
    CC1101_GDOx_CFG_SERIAL_ASYNC_DATA_OUT,
    /* Carrier sense. High if RSSI level is above threshold. Cleared when entering IDLE mode. */
    CC1101_GDOx_CFG_CARRIER_SENSE,
    /* CRC_OK. The last CRC comparison matched. Cleared when entering/restarting RX mode. */
    CC1101_GDOx_CFG_LAST_CRC_OK = 0x0F,
    /* RX_HARD_DATA[1]. Can be used together with RX_SYMBOL_TICK for alternative serial RX output */
    CC1101_GDOx_CFG_RX_HARD_DATA_1 = 0x16,
    /* RX_HARD_DATA[0]. Can be used together with RX_SYMBOL_TICK for alternative serial RX output */
    CC1101_GDOx_CFG_RX_HARD_DATA_0 = 0x17,
    /* PA_PD. Note: PA_PD will have the same signal level in SLEEP and TX states. 
        To control an external PA or RX/TX switch in applications where the SLEEP state is used it is recommended to use GDOx_CFGx=0x2F instead.  */
    CC1101_GDOx_CFG_PA_PD = 0x1B,
    /* LNA_PD. Note: LNA_PD will have the same signal level in SLEEP and RX states. 
        To control an external LNA or RX/TX switch in applications where the SLEEP state is used it is recommended to use GDOx_CFGx=0x2F instead. */
    CC1101_GDOx_CFG_LNA_PD = 0x1C,
    /* RX_SYMBOL_TICK. Can be used together with RX_HARD_DATA for alternative serial RX output. */
    CC1101_GDOx_CFG_RX_SYMBOL_TICK = 0x1D,
    /* WOR_EVENT0 */
    CC1101_GDOx_CFG_WOR_EVENT0 = 0x24,
    /* WOR_EVENT1 */
    CC1101_GDOx_CFG_WOR_EVENT1 = 0x25,
    /* Clock 256 */
    CC1101_GDOx_CFG_CLK_256,
    /* Clock 32k */
    CC1101_GDOx_CFG_CLK_32K,
    /* Chip Ready */
    CC1101_GDOx_CFG_CHIP_RDYn = 0x29,
    /* Crystal Oscillator Stable  */
    CC1101_GDOx_CFG_XOSC_STABLE = 0x2B,
    /* High Impedance (3-state) */
    CC1101_GDOx_CFG_HIGH_IMPEDANCE = 0x2E,
    /* HW to 0 (HW1 achieved by setting GDOx_INV=1). Can be used to control an external LNA/PA or RX/TX switch. */
    CC1101_GDOx_CFG_HW_0_1,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_1,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_1_5,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_2,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_3,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_4,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_6,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_8,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_12,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_16,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_24,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_32,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_48,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_64,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_96,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_128,
    /* There are 3 GDO pins, but only one CLK_XOSC/n can be selected as an output at any time. 
        If CLK_XOSC/n is to be monitored on one of the GDO pins, the other two GDO pins must be configured to values less than 0x30. 
        The GDO0 default value is CLK_XOSC/192. To optimize RF performance, these signals should not be used while the radio is in RX or TX mode. */
    CC1101_GDOx_CFG_CLK_XOSC_192,
    

}cc1101_gdox_cfg_t;



#endif /* CC1101_REG_H */
