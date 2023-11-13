/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _APP_DEFINITIONS_H_
#define _APP_DEFINITIONS_H_

/*${header:start}*/
/*${header:end}*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*${macro:start}*/
#define DEMO_I2S_MASTER_CLOCK_FREQUENCY (24576000)
#define DEMO_I2S_TX                     (I2S0)
#define DEMO_I2S_CLOCK_DIVIDER          (DEMO_I2S_MASTER_CLOCK_FREQUENCY / DEMO_AUDIO_SAMPLE_RATE / DEMO_AUDIO_BIT_WIDTH / 2U)
#define DEMO_DMIC_RX                    (DMIC0)
#define DEMO_DMA                        (DMA0)

#define DMAREQ_DMIC0 23U

#define DEMO_DMIC_RX_CHANNEL DMAREQ_DMIC0
#define DEMO_I2S_TX_CHANNEL  (5)
#define DEMO_I2S_TX_MODE     kI2S_MasterSlaveNormalMaster

#define DEMO_DMIC_CHANNEL        kDMIC_Channel0
#define DEMO_DMIC_CHANNEL_ENABLE DMIC_CHANEN_EN_CH0(1) | DMIC_CHANEN_EN_CH1(1)
#define DEMO_AUDIO_BIT_WIDTH     (16)
#define DEMO_AUDIO_SAMPLE_RATE   (16000)
#define DEMO_AUDIO_PROTOCOL      kCODEC_BusI2S
#define FIFO_DEPTH               (15U)
#define DEMO_VOLUME              (60)
#define ALL_CHANNELS             (0xFF)
/*${macro:end}*/

#endif /* _APP_DEFINITIONS_H_ */
