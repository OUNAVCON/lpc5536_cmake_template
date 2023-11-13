/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "app_definitions.h"
#include "board.h"
#include "streamer_pcm_app.h"
#include "fsl_debug_console.h"
#include "fsl_codec_common.h"

#define RECORD_BUFFER_SIZE (320)
#define BUFFER_NUM         (2U)
#define BUFFER_SIZE        (RECORD_BUFFER_SIZE * BUFFER_NUM)

pcm_rtos_t pcmHandle = {0};

extern codec_handle_t codecHandle;

static uint16_t volatile s_readIndex = 0U;
SDK_ALIGN(dma_descriptor_t s_dmaDescriptorPingpong[BUFFER_NUM], 16);
SDK_ALIGN(static uint8_t s_buffer[BUFFER_SIZE], 16);

static dmic_transfer_t s_receiveXfer[BUFFER_NUM];

static void RxCallback(DMIC_Type *base, dmic_dma_handle_t *handle, status_t status, void *userData)
{
    pcm_rtos_t *pcm       = (pcm_rtos_t *)userData;
    BaseType_t reschedule = -1;
    xSemaphoreGiveFromISR(pcm->semaphoreRX, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

static void TxCallback(I2S_Type *base, i2s_dma_handle_t *handle, status_t completionStatus, void *userData)
{
    pcm_rtos_t *pcm = (pcm_rtos_t *)userData;
    BaseType_t reschedule;
    xSemaphoreGiveFromISR(pcm->semaphoreTX, &reschedule);
    portYIELD_FROM_ISR(reschedule);
}

void streamer_pcm_init(void)
{
    dmic_channel_config_t dmic_channel_cfg;
    DMA_Init(DEMO_DMA);

    DMA_EnableChannel(DEMO_DMA, DEMO_I2S_TX_CHANNEL);
    DMA_SetChannelPriority(DEMO_DMA, DEMO_I2S_TX_CHANNEL, kDMA_ChannelPriority3);
    DMA_CreateHandle(&pcmHandle.i2sTxDmaHandle, DEMO_DMA, DEMO_I2S_TX_CHANNEL);

    DMA_EnableChannel(DEMO_DMA, DEMO_DMIC_RX_CHANNEL);
    DMA_SetChannelPriority(DEMO_DMA, DEMO_DMIC_RX_CHANNEL, kDMA_ChannelPriority2);
    DMA_CreateHandle(&pcmHandle.dmicRxDmaHandle, DEMO_DMA, DEMO_DMIC_RX_CHANNEL);

    memset(&dmic_channel_cfg, 0U, sizeof(dmic_channel_config_t));

    dmic_channel_cfg.divhfclk            = kDMIC_PdmDiv1;
    dmic_channel_cfg.osr                 = 32U;
    dmic_channel_cfg.gainshft            = 3U;
    dmic_channel_cfg.preac2coef          = kDMIC_CompValueZero;
    dmic_channel_cfg.preac4coef          = kDMIC_CompValueZero;
    dmic_channel_cfg.dc_cut_level        = kDMIC_DcCut155;
    dmic_channel_cfg.post_dc_gain_reduce = 1U;
    dmic_channel_cfg.saturate16bit       = 1U;
    dmic_channel_cfg.sample_rate         = kDMIC_PhyFullSpeed;
    DMIC_Init(DMIC0);
    DMIC_Use2fs(DMIC0, true);
    DMIC_EnableChannelDma(DMIC0, DEMO_DMIC_CHANNEL, true);
    DMIC_ConfigChannel(DMIC0, DEMO_DMIC_CHANNEL, kDMIC_Right, &dmic_channel_cfg);
    DMIC_FifoChannel(DMIC0, DEMO_DMIC_CHANNEL, FIFO_DEPTH, true, true);
    DMIC_EnableChannnel(DMIC0, DEMO_DMIC_CHANNEL_ENABLE);
    DMIC_TransferCreateHandleDMA(DMIC0, &pcmHandle.dmicDmaHandle, RxCallback, (void *)&pcmHandle,
                                 &pcmHandle.dmicRxDmaHandle);
    DMIC_InstallDMADescriptorMemory(&pcmHandle.dmicDmaHandle, s_dmaDescriptorPingpong, BUFFER_NUM);

    for (int ibuf = 0; ibuf < BUFFER_NUM; ibuf++)
    {
        s_receiveXfer[ibuf].data                   = &s_buffer[ibuf * RECORD_BUFFER_SIZE];
        s_receiveXfer[ibuf].dataWidth              = sizeof(uint16_t);
        s_receiveXfer[ibuf].dataSize               = RECORD_BUFFER_SIZE / 2;
        s_receiveXfer[ibuf].dataAddrInterleaveSize = kDMA_AddressInterleave2xWidth;
        int ibuf_next                              = ibuf + 1;
        if (ibuf_next == BUFFER_NUM)
            ibuf_next = 0;
        s_receiveXfer[ibuf].linkTransfer = &s_receiveXfer[ibuf_next];
    }
}

pcm_rtos_t *streamer_pcm_open(uint32_t num_buffers)
{
    pcmHandle.semaphoreTX = xSemaphoreCreateBinary();
    return &pcmHandle;
}

pcm_rtos_t *streamer_pcm_rx_open(uint32_t num_buffers)
{
    pcmHandle.semaphoreRX = xSemaphoreCreateBinary();
    return &pcmHandle;
}

void streamer_pcm_start(pcm_rtos_t *pcm)
{
    /* Start the DMIC transfer */
    DMIC_TransferReceiveDMA(DMIC0, &pcm->dmicDmaHandle, s_receiveXfer, DEMO_DMIC_CHANNEL);
}

void streamer_pcm_close(pcm_rtos_t *pcm)
{
    /* Stop playback.  This will flush the SAI transmit buffers. */
    if (pcm->i2sTxHandle.state != 0)
    {
        I2S_TransferAbortDMA(DEMO_I2S_TX, &pcm->i2sTxHandle);
    }
    vSemaphoreDelete(pcmHandle.semaphoreTX);
}

void streamer_pcm_rx_close(pcm_rtos_t *pcm)
{
    /* Abort the DMIC transfer */
    DMIC_TransferAbortReceiveDMA(DMIC0, &pcm->dmicDmaHandle);
    vSemaphoreDelete(pcmHandle.semaphoreRX);
}

int streamer_pcm_write(pcm_rtos_t *pcm, uint8_t *data, uint32_t size)
{
    /* Ensure write size is a multiple of 32, otherwise EDMA will assert
     * failure.  Round down for the last chunk of a file/stream. */
    pcm->i2sTxTransfer.dataSize = size - (size % 32);
    pcm->i2sTxTransfer.data     = data;

    if (pcm->isFirstTx)
    {
        /* Need to queue two transmit buffers so when the first one
         * finishes transfer, the other immediatelly starts */
        I2S_TxTransferSendDMA(DEMO_I2S_TX, &pcm->i2sTxHandle, pcm->i2sTxTransfer);
        pcm->isFirstTx = 0;
    }

    /* Start the consecutive transfer */
    while (I2S_TxTransferSendDMA(DEMO_I2S_TX, &pcm->i2sTxHandle, pcm->i2sTxTransfer) == kStatus_I2S_Busy)
    {
        /* Wait for transfer to finish */
        if (xSemaphoreTake(pcm->semaphoreTX, portMAX_DELAY) != pdTRUE)
        {
            return -1;
        }
    }
    return 0;
}

int streamer_pcm_read(pcm_rtos_t *pcm, uint8_t *data, uint32_t size)
{
    if (pcm->isFirstRx)
    {
        pcm->isFirstRx = 0;
    }
    else
    {
        /* Wait for the previous transfer to finish */
        if (xSemaphoreTake(pcm->semaphoreRX, portMAX_DELAY) != pdTRUE)
            return -1;
        /* Copy data from the DMIC buffer */
        memcpy(data, &s_buffer[s_readIndex], size);
        s_readIndex += size;
        if (s_readIndex >= BUFFER_SIZE)
            s_readIndex -= BUFFER_SIZE;
    }
    return 0;
}

int streamer_pcm_setparams(
    pcm_rtos_t *pcm, uint32_t sample_rate, uint32_t bit_width, uint8_t num_channels, bool tx, bool dummy_tx, int volume)
{
    int ret = 0;

    pcm->isFirstTx    = tx ? 1U : pcm->isFirstTx;
    pcm->isFirstRx    = tx ? pcm->isFirstRx : 1U;
    pcm->sample_rate  = sample_rate;
    pcm->bit_width    = bit_width;
    pcm->num_channels = num_channels;
    pcm->dummy_tx_enable |= dummy_tx;

    /*
     * masterSlave = kI2S_MasterSlaveNormalMaster;
     * mode = kI2S_ModeI2sClassic;
     * rightLow = false;
     * leftJust = false;
     * pdmData = false;
     * sckPol = false;
     * wsPol = false;
     * divider = 1;
     * oneChannel = false;
     * dataLength = 16;
     * frameLength = 32;
     * position = 0;
     * fifoLevel = 4;
     */

    if (tx)
    {
        I2S_TxGetDefaultConfig(&pcm->tx_config);
        pcm->tx_config.divider     = DEMO_I2S_CLOCK_DIVIDER;
        pcm->tx_config.masterSlave = DEMO_I2S_TX_MODE;
        I2S_TxInit(DEMO_I2S_TX, &pcm->tx_config);
        I2S_TxTransferCreateHandleDMA(DEMO_I2S_TX, &pcm->i2sTxHandle, &pcm->i2sTxDmaHandle, TxCallback,
                                      (void *)&pcmHandle);
    }

    ret = CODEC_SetMute(&codecHandle, ALL_CHANNELS, true);
    ret = streamer_pcm_set_volume(pcm, DEMO_VOLUME);
    if (ret != kStatus_Success)
    {
        return 1;
    }

    return 0;
}

void streamer_pcm_getparams(pcm_rtos_t *pcm, uint32_t *sample_rate, uint32_t *bit_width, uint8_t *num_channels)
{
    *sample_rate  = pcm->sample_rate;
    *bit_width    = pcm->bit_width;
    *num_channels = pcm->num_channels;
}

int streamer_pcm_mute(pcm_rtos_t *pcm, bool mute)
{
    status_t ret;
    ret = CODEC_SetMute(&codecHandle, ALL_CHANNELS, mute);
    if (ret != kStatus_Success)
    {
        return 1;
    }

    return 0;
}

int streamer_pcm_set_volume(pcm_rtos_t *pcm, int volume)
{
    int channel;
    channel = (pcm->num_channels == 1) ? kCODEC_PlayChannelHeadphoneLeft | kCODEC_PlayChannelSpeakerLeft : ALL_CHANNELS;

    if (volume <= 0)
        CODEC_SetMute(&codecHandle, ALL_CHANNELS, true);
    else
        CODEC_SetVolume(&codecHandle, channel, volume > CODEC_VOLUME_MAX_VALUE ? CODEC_VOLUME_MAX_VALUE : volume);

    return 0;
}
