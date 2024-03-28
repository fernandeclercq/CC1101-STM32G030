#include "spi.h"

volatile uint8_t time_out = 0;
volatile uint8_t temp = 0;


// PA1 SPI1_SCK     (PIN 8)
// PA2 SPI1_MOSI    (PIN 9)
// PA6 SPI1_MISO    (PIN 13)
// PA4 SPI1_CS      (PIN 11)



void spi1_init(void)
{
    time_out = 0;
    /******************************************************************************/
    /*************************** GPIO Configuration *******************************/

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_ALTERNATE); // SCK
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_1, LL_GPIO_AF_0);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_1, LL_GPIO_SPEED_FREQ_HIGH);

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_ALTERNATE); // MOSI
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_2, LL_GPIO_AF_0);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_2, LL_GPIO_SPEED_FREQ_HIGH);

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE); // MISO
    LL_GPIO_SetAFPin_0_7(GPIOA, LL_GPIO_PIN_6, LL_GPIO_AF_0);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);

    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT); // CS as output
    LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_4, LL_GPIO_SPEED_FREQ_HIGH);

    /******************************************************************************/

    /**************************** SPI Configuration *******************************/

    // Enable Clock for SPI1 Peripheral
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
    // Set the Clock for the SPI (8MHz)
    LL_SPI_SetBaudRatePrescaler(SPI1, LL_SPI_BAUDRATEPRESCALER_DIV2);

    // Set the clock polarity and phase polarity (Mode 0)
    LL_SPI_SetClockPhase(SPI1, LL_SPI_PHASE_1EDGE);
    LL_SPI_SetClockPolarity(SPI1, LL_SPI_POLARITY_LOW);

    // Enable Full-Duplex
    LL_SPI_SetTransferDirection(SPI1, LL_SPI_FULL_DUPLEX);

    // Set MSB First
    LL_SPI_SetTransferBitOrder(SPI1, LL_SPI_MSB_FIRST);

    // Set Mode to SPI Master
    LL_SPI_SetMode(SPI1, LL_SPI_MODE_MASTER);

    // Set Data size (8 bit width)
    LL_SPI_SetDataWidth(SPI1, LL_SPI_DATAWIDTH_8BIT);

    // Set CS to be managed by software
    LL_SPI_SetNSSMode(SPI1, LL_SPI_NSS_SOFT);
    LL_SPI_DisableNSSPulseMgt(SPI1);

    LL_SPI_DisableDMAReq_RX(SPI1);
    LL_SPI_DisableDMAReq_TX(SPI1);

    LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);

    LL_SPI_DisableCRC(SPI1);
    
    LL_SPI_Enable(SPI1);

    delay_ms(1);

}


void spi1_transmit_bytes(uint8_t * data, uint32_t size)
{
    
    uint32_t counter = 0;
    for(counter = 0; counter < size; counter++)
    {
        spi1_transmit_byte(data[counter]);
    }

}

void spi1_receive_bytes(uint8_t * data, uint32_t size)
{
    uint32_t counter = 0;
    for(counter = 0; counter < size; counter++)
    {
        spi1_receive_byte(&data[counter]);
    }

}

void spi1_receive_byte(uint8_t * data)
{

    // Send dummy data
    LL_SPI_TransmitData8(SPI1, 0x00);

    /* Wait for the RXNE to be set*/
    while((LL_SPI_IsActiveFlag_RXNE(SPI1))){}

    /* Read received data */
    *data = LL_SPI_ReceiveData8(SPI1);

}

void spi1_transmit_byte(uint8_t data)
{   
    temp = 0;

    // Wait until the Transmit Buffer is Empty
    while(!(LL_SPI_IsActiveFlag_TXE(SPI1))){}

    // When there is space in the buffer, write the data to the register
    LL_SPI_TransmitData8(SPI1, data);

    /* Wait for the TXE again to be set */
    while(!(LL_SPI_IsActiveFlag_TXE(SPI1))){}

    /* Wait for BUSY flag to reset */
    while(LL_SPI_IsActiveFlag_BSY(SPI1)){}

    /* Clear OVR flag */
    temp = LL_SPI_ReceiveData8(SPI1);
    temp = (uint8_t)SPI1->SR;

}

void spi1_wait_miso(void)
{
    time_out = 0;
    /* Wait the SPI MISO to go low (CC1200 Ready for SPI Transfer) */
    while((LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_6)))
    {
        // Time out after 200ms
        if(time_out > 200)
        {
            return;
        }
        time_out++;
        delay_ms(1);
    }

}

void spi1_cs_enable(void)
{
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);

}

void spi1_cs_disable(void)
{
    LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4);
}