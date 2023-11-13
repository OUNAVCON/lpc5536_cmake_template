/*
 * Copyright 2022 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_STREAMER_PCM_APP_H_
#define _FSL_STREAMER_PCM_APP_H_

#include "fsl_dmic.h"
#include "fsl_dmic_dma.h"
#include "fsl_i2c.h"
#include "fsl_i2s.h"
#include "fsl_i2s_dma.h"
#include "fsl_wm8904.h"
#include "FreeRTOS.h"
#include "semphr.h"

#include "streamer_pcm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief PCM interface structure */
struct _pcm_rtos_t
{
    dma_handle_t i2sTxDmaHandle;
    i2s_dma_handle_t i2sTxHandle;
    i2s_config_t tx_config;
    i2s_transfer_t i2sTxTransfer;

    dmic_dma_handle_t dmicDmaHandle;
    dma_handle_t dmicRxDmaHandle;

    uint32_t sample_rate;
    uint32_t bit_width;
    uint8_t num_channels;

    SemaphoreHandle_t semaphoreRX;
    SemaphoreHandle_t semaphoreTX;

    uint8_t isFirstRx;
    uint8_t isFirstTx;

    bool dummy_tx_enable;
};

#endif
