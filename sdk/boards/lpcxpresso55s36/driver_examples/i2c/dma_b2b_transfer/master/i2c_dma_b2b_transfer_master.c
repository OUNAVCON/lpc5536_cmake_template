/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/*  SDK Included Files */
#include "pin_mux.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_i2c_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_I2C_MASTER_BASE    (I2C2_BASE)
#define I2C_MASTER_CLOCK_FREQUENCY (12000000)

#define EXAMPLE_DMA                DMA0
#define EXAMPLE_I2C_MASTER_CHANNEL 11

#define EXAMPLE_I2C_MASTER ((I2C_Type *)EXAMPLE_I2C_MASTER_BASE)

#define I2C_MASTER_SLAVE_ADDR_7BIT (0x7EU)
#define I2C_BAUDRATE               (100000) /* 100K */
#define I2C_DATA_LENGTH            (33)     /* MAX is 256 */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t g_master_txBuff[I2C_DATA_LENGTH];
uint8_t g_master_rxBuff[I2C_DATA_LENGTH];

i2c_master_dma_handle_t g_m_dma_handle;
dma_handle_t dmaHandle;
volatile bool g_MasterCompletionFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/

static void i2c_master_dma_callback(I2C_Type *base, i2c_master_dma_handle_t *handle, status_t status, void *userData)
{
    /* Signal transfer success when received success status. */
    if (status == kStatus_Success)
    {
        g_MasterCompletionFlag = true;
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    i2c_master_config_t masterConfig;
    i2c_master_transfer_t masterXfer;

    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom0Clk, 0u, false);
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom0Clk, 1u, true);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    /* attach 12 MHz clock to FLEXCOMM2 (I2C master) */
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 0u, false);
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom2Clk, 1u, true);
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);

    /* reset FLEXCOMM for I2C */
    RESET_PeripheralReset(kFC2_RST_SHIFT_RSTn);

    BOARD_InitPins();
    BOARD_BootClockPLL150M();
    BOARD_InitDebugConsole();

    DMA_Init(EXAMPLE_DMA);

    PRINTF("\r\nI2C board2board DMA example -- Master transfer.\r\n");

    /* Set up i2c master to send data to slave*/
    /* First data in txBuff is data length of the transmiting data. */
    g_master_txBuff[0] = I2C_DATA_LENGTH - 1U;
    for (uint32_t i = 1U; i < I2C_DATA_LENGTH; i++)
    {
        g_master_txBuff[i] = i - 1;
    }

    PRINTF("Master will send data :");
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH - 1U; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_txBuff[i + 1]);
    }
    PRINTF("\r\n\r\n");

    /*
     * masterConfig.baudRate_Bps = 100000U;
     * masterConfig.enableStopHold = false;
     * masterConfig.glitchFilterWidth = 0U;
     * masterConfig.enableMaster = true;
     */
    I2C_MasterGetDefaultConfig(&masterConfig);

    /* Change the default baudrate configuration */
    masterConfig.baudRate_Bps = I2C_BAUDRATE;

    /* Initialize the I2C master peripheral */
    I2C_MasterInit(EXAMPLE_I2C_MASTER, &masterConfig, I2C_MASTER_CLOCK_FREQUENCY);

    memset(&g_m_dma_handle, 0, sizeof(g_m_dma_handle));
    memset(&masterXfer, 0, sizeof(masterXfer));

    /* subAddress = 0x01, data = g_master_txBuff - write to slave.
      start + slaveaddress(w) + subAddress + length of data buffer + data buffer + stop*/
    uint8_t deviceAddress     = 0x01U;
    masterXfer.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;
    masterXfer.direction      = kI2C_Write;
    masterXfer.subaddress     = (uint32_t)deviceAddress;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = g_master_txBuff;
    masterXfer.dataSize       = I2C_DATA_LENGTH;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    DMA_EnableChannel(EXAMPLE_DMA, EXAMPLE_I2C_MASTER_CHANNEL);
    DMA_CreateHandle(&dmaHandle, EXAMPLE_DMA, EXAMPLE_I2C_MASTER_CHANNEL);

    I2C_MasterTransferCreateHandleDMA(EXAMPLE_I2C_MASTER, &g_m_dma_handle, i2c_master_dma_callback, NULL, &dmaHandle);
    I2C_MasterTransferDMA(EXAMPLE_I2C_MASTER, &g_m_dma_handle, &masterXfer);

    /*  wait for transfer completed. */
    while (!g_MasterCompletionFlag)
    {
    }
    g_MasterCompletionFlag = false;

    PRINTF("Receive sent data from slave :");

    /* subAddress = 0x01, data = g_master_rxBuff - read from slave.
      start + slaveaddress(w) + subAddress + repeated start + slaveaddress(r) + rx data buffer + stop */
    masterXfer.slaveAddress   = I2C_MASTER_SLAVE_ADDR_7BIT;
    masterXfer.direction      = kI2C_Read;
    masterXfer.subaddress     = (uint32_t)deviceAddress;
    masterXfer.subaddressSize = 1;
    masterXfer.data           = g_master_rxBuff;
    masterXfer.dataSize       = I2C_DATA_LENGTH - 1;
    masterXfer.flags          = kI2C_TransferDefaultFlag;

    I2C_MasterTransferDMA(EXAMPLE_I2C_MASTER, &g_m_dma_handle, &masterXfer);

    /*  Reset master completion flag to false. */
    g_MasterCompletionFlag = false;

    /*  Wait for transfer completed. */
    while (!g_MasterCompletionFlag)
    {
    }
    g_MasterCompletionFlag = false;

    for (uint32_t i = 0U; i < I2C_DATA_LENGTH - 1; i++)
    {
        if (i % 8 == 0)
        {
            PRINTF("\r\n");
        }
        PRINTF("0x%2x  ", g_master_rxBuff[i]);
    }
    PRINTF("\r\n\r\n");

    /* Transfer completed. Check the data.*/
    for (uint32_t i = 0U; i < I2C_DATA_LENGTH - 1; i++)
    {
        if (g_master_rxBuff[i] != g_master_txBuff[i + 1])
        {
            PRINTF("\r\nError occurred in the transfer ! \r\n");
            break;
        }
    }

    PRINTF("\r\nEnd of I2C example .\r\n");
    while (1)
    {
    }
}
