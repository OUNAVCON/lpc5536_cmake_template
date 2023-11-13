/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* This is a generic configuration file of the motor control driver. You need to edit the file.
 * Remove this warning statement after this file is edited manually or
 * re-generate this file using MC_PMSM Config Tool component.
 */

#ifndef _MC_PERIPH_INIT_H_
#define _MC_PERIPH_INIT_H_

#include "fsl_device_registers.h"
#include "pin_mux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Independent register definitions for baremetal port init */
#define PIO_MODE_INACTIVE	0b00
#define PIO_MODE_PULLDOWN       0b01
#define PIO_MODE_PULLUP		0b10
#define PIO_MODE_REPEATER	0b11

#define PIO_SLEW_STANDARD	0b0
#define PIO_SLEW_FAST		0b1

#define PIO_INVERT_DIS		0b0
#define PIO_INVERT_EN		0b1

#define PIO_DMODE_DIS		0b0
#define PIO_DMODE_EN		0b1

#define PIO_OD_DIS			0b0
#define PIO_OD_EN			0b1

#define PIO_ASW_DIS			0b0
#define PIO_ASW_EN			0b1

#define PIO_FILTEROFF_EN	0b0
#define PIO_FILTEROFF_DIS	0b1

#define PIO_FUNC_0			0x0
#define PIO_FUNC_1			0x1
#define PIO_FUNC_2			0x2
#define PIO_FUNC_3			0x3
#define PIO_FUNC_4			0x4
#define PIO_FUNC_5			0x5
#define PIO_FUNC_6			0x6
#define PIO_FUNC_7			0x7
#define PIO_FUNC_8			0x8
#define PIO_FUNC_9			0x9
#define PIO_FUNC_10			0xA
#define PIO_FUNC_11			0xB
#define PIO_FUNC_12			0xC
#define PIO_FUNC_13			0xD
#define PIO_FUNC_14			0xE
#define PIO_FUNC_15			0xF

#define ADC0_CLK_FRO 		2U
#define CTIMER_CLK_FRO 		3U

/* Define port and pins for serial communication */
#define PORT_USART0             0U
#define PIN_USART_TX            30U             /* USART0_TX */
#define PIN_USART_RX            29U             /* USART0_RX */

/* Define ports and pins for PWM phases */ 
#define PORT_PWM_AT             1U
#define PORT_PWM_AB             1U
#define PORT_PWM_BT             1U
#define PORT_PWM_BB             1U
#define PORT_PWM_CT             1U
#define PORT_PWM_CB             1U
#define PIN_PWM_AT              20U             /* PWM_AT <- PWM0_A0 */
#define PIN_PWM_AB              17U             /* PWM_AB <- PWM0_B0 */
#define PIN_PWM_BT              6U              /* PWM_BT <- PWM0_A1 */
#define PIN_PWM_BB              22U             /* PWM_BB <- PWM0_B1 */
#define PIN_PWM_CT              8U              /* PWM_CT <- PWM0_A2 */
#define PIN_PWM_CB              4U              /* PWM_CB <- PWM0_B2 */

/* Define ports and pins for ADC measure */
#define PORT_ADC_CUR_A          0U
#define PORT_ADC_CUR_B          0U
#define PORT_ADC_CUR_C          0U
#define PORT_ADC_VOLT_DCB       0U
#define PIN_ADC_CUR_A           15U             /* Current A   -> ADC0_CH3A */
#define PIN_ADC_CUR_B           31U             /* Current B   -> ADC0_CH8A */
#define PIN_ADC_CUR_C           16U             /* Current C   -> ADC0_CH3B */
#define PIN_ADC_VOLT_DCB        10U             /* Voltage DCB -> ADC0_CH1A */

/* Define port and pin for HSCMP */
#define PORT_HSCMP              1U
#define PIN_HSCMP_IN            5U              /* Current DCB -> HSCMP0_IN3 */

/* Define ports and pins for ENC phases */
#define PORT_ENC_PH_A           0U
#define PORT_ENC_PH_B           0U
#define PIN_ENC0_PHASEA         13U             /* Encoder Phase A -> ENC0_PHA */ 
#define PIN_ENC0_PHASEB         14U             /* Encoder Phase B -> ENC0_PHB */

/* Hardware scales and thresholds */
#define I_MAX_SCALE                     8.25F           /* Current scale */
#define U_DCB_MAX_SCALE                 60.8F           /* DC bus voltage scale */
#define HSCMP_THRESHOLD_CURRENT(x)      (uint8_t)((x / I_MAX_SCALE) * (float)255U)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void InitPins(void);
void InitADC0(void);
void InitHsCmp0(void);
void InitPWM0(void);
void InitSlowLoop(void);
void InitClock(void);
void InitInputmux(void);


/******************************************************************************
 * Timing
 ******************************************************************************/
/* MCU core clock in Hz */
#define MCU_CLOCK_FREQ          (150000000U)
/* PWM frequency in Hz*/
#define M1_PWM_FREQ             (10000U)
/* PWM modulo = FTM_input_clock / M1_PWM_FREQ */
#define M1_PWM_MODULO           (MCU_CLOCK_FREQ / M1_PWM_FREQ)
/* Output PWM deadtime value in nanoseconds */
#define M1_PWM_DEADTIME (500)
/* PWM vs. Fast control loop ratio */
#define M1_FOC_FREQ_VS_PWM_FREQ (1U)
/* Slow control loop frequency */
#define M1_SLOW_LOOP_FREQ       (1000U)

#endif /* _MC_PERIPH_INIT_H_  */
