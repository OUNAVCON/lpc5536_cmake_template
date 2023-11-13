/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mc_periph_init.h"
#include "fsl_common.h"
#include "fsl_power.h"
#include "pin_mux.h"
#include "fsl_inputmux_connections.h"
/*******************************************************************************
 * Defines
 ******************************************************************************/
#define INPUTMUX_SDK_MASK   0x003F

/*******************************************************************************
 * Typedef
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Local functions
 ******************************************************************************/

void InitPins(void)
{
    /* Enable clocks for all GPIOs */
    SYSCON->AHBCLKCTRLSET[0] = SYSCON_AHBCLKCTRL0_GPIO0_MASK
                              | SYSCON_AHBCLKCTRL0_GPIO1_MASK
                              | SYSCON_AHBCLKCTRL0_GPIO2_MASK
                              | SYSCON_AHBCLKCTRL0_GPIO3_MASK
                              | SYSCON_AHBCLKCTRL0_IOCON_MASK
                              | SYSCON_AHBCLKCTRL0_MUX_MASK;
    
    /* Initialization pins for USART communication */
    IOCON->PIO[PORT_USART0][PIN_USART_RX] = ((IOCON->PIO[PORT_USART0][PIN_USART_RX] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT029 (pin 93) is configured as FC0_RXD_SDA_MOSI_DATA. */
                         | IOCON_PIO_FUNC(PIO_FUNC_1)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO_DMODE_EN));

    IOCON->PIO[PORT_USART0][PIN_USART_TX] = ((IOCON->PIO[PORT_USART0][PIN_USART_TX] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT030 (pin 95) is configured as FC0_TXD_SCL_MISO_WS. */
                         | IOCON_PIO_FUNC(PIO_FUNC_1)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO_DMODE_EN));

    /* Initialization pins for PWM */
    IOCON->PIO[PORT_PWM_AB][PIN_PWM_AB] = ((IOCON->PIO[PORT_PWM_AB][PIN_PWM_AB] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT117 (pin 91) is configured as PWM0_B0. */
                         | IOCON_PIO_FUNC(PIO_FUNC_11)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_17_DIGIMODE_DIGITAL));

    IOCON->PIO[PORT_PWM_AT][PIN_PWM_AT] = ((IOCON->PIO[PORT_PWM_AT][PIN_PWM_AT] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT120 (pin 11) is configured as PWM0_A0. */
                         | IOCON_PIO_FUNC(PIO_FUNC_11)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO_DMODE_EN));

    IOCON->PIO[PORT_PWM_BB][PIN_PWM_BB] = ((IOCON->PIO[PORT_PWM_BB][PIN_PWM_BB] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT122 (pin 40) is configured as PWM0_B1. */
                         | IOCON_PIO_FUNC(PIO_FUNC_11)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO_DMODE_EN));

    IOCON->PIO[PORT_PWM_CB][PIN_PWM_CB] = ((IOCON->PIO[PORT_PWM_CB][PIN_PWM_CB] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Signal(function) select: PORT14 (pin 75) is configured as PWM0_B2. */
                        | IOCON_PIO_FUNC(PIO_FUNC_11)

                        /* Select Digital mode: Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO_DMODE_EN));

    IOCON->PIO[PORT_PWM_BT][PIN_PWM_BT] = ((IOCON->PIO[PORT_PWM_BT][PIN_PWM_BT] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Signal(function) select: PORT16 (pin 50) is configured as PWM0_A1. */
                        | IOCON_PIO_FUNC(PIO_FUNC_11)

                        /* Select Digital mode: Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO_DMODE_EN));

    IOCON->PIO[PORT_PWM_CT][PIN_PWM_CT] = ((IOCON->PIO[PORT_PWM_CT][PIN_PWM_CT] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Signal(function) select: PORT18 (pin 36) is configured as PWM0_A2. */
                        | IOCON_PIO_FUNC(PIO_FUNC_11)

                        /* Select Digital mode: Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO_DMODE_EN));
    
    
    /* Initialization pins for ADC */
    /* Input Voltage DCB */
    GPIO->DIR[PORT_ADC_VOLT_DCB] &= ~(1UL << PIN_ADC_VOLT_DCB);
    IOCON->PIO[PORT_ADC_VOLT_DCB][PIN_ADC_VOLT_DCB] = ((IOCON->PIO[PORT_ADC_VOLT_DCB][PIN_ADC_VOLT_DCB] &
                      /* Mask bits to zero which are setting */
                      (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                     /* Signal(function) select: PORT010 (pin 21) is configured as ADC0_1A. */
                     | IOCON_PIO_FUNC(PIO_FUNC_0)

                     /* Select Digital mode: Disable digital mode.
                      * Digital input set to 0. */
                     | IOCON_PIO_DIGIMODE(PIO_DMODE_DIS));

    /* Input Current A */
    GPIO->DIR[PORT_ADC_CUR_A] &= ~(1UL << PIN_ADC_CUR_A);
    IOCON->PIO[PORT_ADC_CUR_A][PIN_ADC_CUR_A] = ((IOCON->PIO[PORT_ADC_CUR_A][PIN_ADC_CUR_A] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT015 (pin 22) is configured as ADC0_3A. */
                         | IOCON_PIO_FUNC(PIO_FUNC_0)

                         /* Select Digital mode: Disable digital mode.
                          * Digital input set to 0. */
                         | IOCON_PIO_DIGIMODE(PIO_DMODE_DIS));

    /* Input Current B */
    GPIO->DIR[PORT_ADC_CUR_B] &= ~(1UL << PIN_ADC_CUR_B);
    IOCON->PIO[PORT_ADC_CUR_B][PIN_ADC_CUR_B] = ((IOCON->PIO[PORT_ADC_CUR_B][PIN_ADC_CUR_B] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_ASW0_MASK)))

                         /* Signal(function) select: PORT031 (pin 23) is configured as ADC0_8A. */
                         | IOCON_PIO_FUNC(PIO_FUNC_0)

                         /* Mode select (on-chip pull-up/pull-down resistor control): Inactive.
                          * Inactive (no pull-down/pull-up resistor enabled). */
                         | IOCON_PIO_MODE(PIO_MODE_INACTIVE)

                         /* Select Digital mode: Disable digital mode.
                          * Digital input set to 0. */
                         | IOCON_PIO_DIGIMODE(PIO_DMODE_DIS)

                         /* Analog switch input control: Analog switch is closed.
                          * (enable). */
                         | IOCON_PIO_ASW0(PIO_ASW_EN));
    
    /* Input Current C */
    GPIO->DIR[PORT_ADC_CUR_C] &= ~(1UL << PIN_ADC_CUR_C);
    IOCON->PIO[PORT_ADC_CUR_C][PIN_ADC_CUR_C] = ((IOCON->PIO[PORT_ADC_CUR_C][PIN_ADC_CUR_C] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT016 (pin 20) is configured as ADC0_3B. */
                         | IOCON_PIO_FUNC(PIO_FUNC_0)

                         /* Select Digital mode: Disable digital mode.
                          * Digital input set to 0. */
                         | IOCON_PIO_DIGIMODE(PIO_DMODE_DIS));
    
    /* Initialization pin for HSCMP */
    IOCON->PIO[PORT_HSCMP][PIN_HSCMP_IN] = ((IOCON->PIO[PORT_HSCMP][PIN_HSCMP_IN] &
                     /* Mask bits to zero which are setting */
                     (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK | IOCON_PIO_ASW0_MASK)))

                    /* Signal(function) select: PORT15 (pin 35) is configured as HSCMP0_IN3. */
                    | IOCON_PIO_FUNC(PIO_FUNC_0)

                    /* Mode select (on-chip pull-up/pull-down resistor control): Inactive.
                     * Inactive (no pull-down/pull-up resistor enabled). */
                    | IOCON_PIO_MODE(PIO_MODE_INACTIVE)

                    /* Select Digital mode: Disable digital mode.
                     * Digital input set to 0. */
                    | IOCON_PIO_DIGIMODE(PIO_DMODE_DIS)

                    /* Analog switch input control: Analog switch is closed.
                     * (enable). */
                    | IOCON_PIO_ASW0(PIO_ASW_EN));
}


  /*!
   * @brief   void InitPWM0(void)
   *           - Initialization of the eFlexPWM0 peripheral for motor M1
   *           - 3-phase center-aligned PWM
   *
   * @param   void
   *
   * @return  none
   */
void InitPWM0(void)
{
	PWM_Type *PWMBase = (PWM_Type *)PWM0;

	/* Enable clock to PWM */
	SYSCON->AHBCLKCTRLSET[3] = SYSCON_AHBCLKCTRL3_PWM0_MASK;
	/* Enable clock to submodules */
	SYSCON->PWM0SUBCTL = (SYSCON_PWM0SUBCTL_CLK0_EN_MASK | SYSCON_PWM0SUBCTL_CLK1_EN_MASK | SYSCON_PWM0SUBCTL_CLK2_EN_MASK | SYSCON_PWM0SUBCTL_CLK3_EN_MASK);
	/* Value register initial values, duty cycle 50% */
	PWMBase->SM[0].INIT = PWM_INIT_INIT((uint16_t)(-(M1_PWM_MODULO / 2)));
	PWMBase->SM[1].INIT = PWM_INIT_INIT((uint16_t)(-(M1_PWM_MODULO / 2)));
	PWMBase->SM[2].INIT = PWM_INIT_INIT((uint16_t)(-(M1_PWM_MODULO / 2)));
	PWMBase->SM[3].INIT = PWM_INIT_INIT((uint16_t)(-(M1_PWM_MODULO / 2)));

	PWMBase->SM[0].VAL1 = PWM_VAL1_VAL1((uint16_t)((M1_PWM_MODULO / 2) - 1));
	PWMBase->SM[1].VAL1 = PWM_VAL1_VAL1((uint16_t)((M1_PWM_MODULO / 2) - 1));
	PWMBase->SM[2].VAL1 = PWM_VAL1_VAL1((uint16_t)((M1_PWM_MODULO / 2) - 1));
	PWMBase->SM[3].VAL1 = PWM_VAL1_VAL1((uint16_t)((M1_PWM_MODULO / 2) - 1));

	PWMBase->SM[0].VAL2 = 0;
	PWMBase->SM[1].VAL2 = 0;
	PWMBase->SM[2].VAL2 = 0;
	PWMBase->SM[3].VAL2 = 0;

	PWMBase->SM[0].VAL3 = 0;
	PWMBase->SM[1].VAL3 = 0;
	PWMBase->SM[2].VAL3 = 0;
	PWMBase->SM[3].VAL3 = 0;

	/* PWM0 module 0 trigger on VAL4 enabled for ADC synchronization */
	PWMBase->SM[0].VAL4 = PWM_VAL4_VAL4((uint16_t)((-(M1_PWM_MODULO / 2))));
	PWMBase->SM[0].TCTRL |= PWM_TCTRL_OUT_TRIG_EN(1 << 4);

	/* Set deadtime (number of Fast Peripheral Clocks) DTCNT0,1 = T_dead * f_fpc = 0.5us * 150MHz = 75 */
	PWMBase->SM[0].DTCNT0 = ((M1_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
	PWMBase->SM[1].DTCNT0 = ((M1_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
	PWMBase->SM[2].DTCNT0 = ((M1_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
	PWMBase->SM[3].DTCNT0 = ((M1_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
	PWMBase->SM[0].DTCNT1 = ((M1_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
	PWMBase->SM[1].DTCNT1 = ((M1_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
	PWMBase->SM[2].DTCNT1 = ((M1_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
	PWMBase->SM[3].DTCNT1 = ((M1_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);

	/* Full cycle reload */
	PWMBase->SM[0].CTRL |= PWM_CTRL_FULL_MASK;
	PWMBase->SM[1].CTRL |= PWM_CTRL_FULL_MASK;
	PWMBase->SM[2].CTRL |= PWM_CTRL_FULL_MASK;
	PWMBase->SM[3].CTRL |= PWM_CTRL_FULL_MASK;

	/* Fault0 (HSCMP0_OUT or AOI0 event 0) trigger */
	PWMBase->SM[0].DISMAP[0] = 0xF111U;
	PWMBase->SM[1].DISMAP[0] = 0xF111U;
	PWMBase->SM[2].DISMAP[0] = 0xF111U;
	PWMBase->SM[3].DISMAP[0] = 0xF111U;

	/* PWMs are re-enabled at PWM full cycle */
	PWMBase->FSTS = (PWMBase->FSTS & ~PWM_FSTS_FFULL_MASK) | PWM_FSTS_FFULL(0x1);

	/* PWM fault filter - 3 Fast periph. clocks sample rate, 5 agreeing samples to activate */
	PWMBase->FFILT = (PWMBase->FFILT & ~PWM_FFILT_FILT_PER_MASK) | PWM_FFILT_FILT_PER(2);

	/* All interrupts disabled, safe manual fault clearing, inversed logic (trigger level = high) */
	PWMBase->FCTRL &= ~(PWM_FCTRL_FLVL_MASK | PWM_FCTRL_FAUTO_MASK | PWM_FCTRL_FSAFE_MASK | PWM_FCTRL_FIE_MASK);	/* Clear FCTRL register prior further settings */
	PWMBase->FCTRL |= PWM_FCTRL_FIE(0U); /* FAULT 0 & FAULT 1 - Interrupt disable */

	/* Inverse the fault logic (DCB current overcurrent signal are active high. */
	PWMBase->FCTRL |= PWM_FCTRL_FLVL(0xFU);

	PWMBase->FCTRL |= PWM_FCTRL_FAUTO(0U);
	PWMBase->FCTRL |= PWM_FCTRL_FSAFE(0xFU);

	/* Clear all fault flags */
	PWMBase->FSTS = (PWMBase->FSTS & ~PWM_FSTS_FFLAG_MASK) | PWM_FSTS_FFLAG(0xF);

	/* Start PWMs (set load OK flags and run - we need to trigger the ADC) */
	PWMBase->MCTRL = (PWMBase->MCTRL & ~PWM_MCTRL_CLDOK_MASK) | PWM_MCTRL_CLDOK(0xF);
	PWMBase->MCTRL = (PWMBase->MCTRL & ~PWM_MCTRL_LDOK_MASK) | PWM_MCTRL_LDOK(0xF);
	PWMBase->MCTRL = (PWMBase->MCTRL & ~PWM_MCTRL_RUN_MASK) | PWM_MCTRL_RUN(0xF);
}

  /*!
   * @brief   void InitADC0(void)
   *           - Initialization of the ADC0 peripheral
   *           - Initialization of the A/D converter for current and voltage sensing
   *
   * @param   void
   *
   * @return  none
   */

void InitADC0(void)
{
	uint32_t GCCa;
	uint32_t GCCb;
	uint32_t GCRa;
	uint32_t GCRb;

	/* Clock divider setup */
	/* Reset counter */
	SYSCON->ADC0CLKDIV = SYSCON_ADC0CLKDIV_RESET_MASK;
	/* Set division to 2 */
	SYSCON->ADC0CLKDIV = (2U - 1U);

	/* Attach FRO_HF to ADC0 */
	SYSCON->ADC0CLKSEL =  ADC0_CLK_FRO & SYSCON_ADC0CLKSEL_SEL_MASK;

	/* Disable VREF power down */
	PMC->PDRUNCFGCLR0 = PMC_PDRUNCFG0_PDEN_VREF_MASK;        
        
	/* Init ADC */
	/* Enable the clock. */
	SYSCON->AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_ADC0_MASK;

	/* Reset the module. */
	ADC0->CTRL |= ADC_CTRL_RST_MASK;          /* ADC logic reset */
	ADC0->CTRL &= ~ADC_CTRL_RST_MASK;
	ADC0->CTRL |= ADC_CTRL_RSTFIFO0_MASK;     /* Reset FIFO 0 */
	ADC0->CTRL |= ADC_CTRL_RSTFIFO1_MASK;     /* Reset FIFO 1 */

	/* Disable the module before setting configuration. */
	ADC0->CTRL &= ~ADC_CTRL_ADCEN_MASK;

	/* Configure the module generally. */
	ADC0->CTRL &= ~ADC_CTRL_DOZEN_MASK;

	/* Set calibration average mode. */
	ADC0->CTRL = ADC_CTRL_CAL_AVGS(7U);

	/* ADC0 configuration. */
	ADC0->CFG |= ADC_CFG_PWREN_MASK  |  /* ADC analog circuits pre-enable */
			ADC_CFG_PUDLY(0x80) |  /* Power up delay */
			ADC_CFG_REFSEL(2U)  |  /* Reference voltage */
			ADC_CFG_PWRSEL(3U);    /* Power configuration */

	/* Enable the module after setting configuration. */
	ADC0->CTRL |= ADC_CTRL_ADCEN_MASK;

	/* Offset calibration. */
	ADC0->CTRL |= ADC_CTRL_CALOFS_MASK;
	while (ADC_STAT_CAL_RDY_MASK != (ADC0->STAT & ADC_STAT_CAL_RDY_MASK))
	{
	}

	/* AutoCalibration */
	assert((0u == ((ADC_FCTRL_FCOUNT_MASK & ADC0->FCTRL[0]) >> ADC_FCTRL_FCOUNT_SHIFT))
			&& (0u == ((ADC_FCTRL_FCOUNT_MASK & ADC0->FCTRL[1]) >> ADC_FCTRL_FCOUNT_SHIFT)));

	/* Request gain calibration. */
	ADC0->CTRL |= ADC_CTRL_CAL_REQ_MASK;
	while ((ADC_GCC_RDY_MASK != (ADC0->GCC[0] & ADC_GCC_RDY_MASK)) ||
			(ADC_GCC_RDY_MASK != (ADC0->GCC[1] & ADC_GCC_RDY_MASK)))
	{
	}

	/* Calculate gain offset. */
	GCCa = (ADC0->GCC[0] & ADC_GCC_GAIN_CAL_MASK);
	GCCb = (ADC0->GCC[1] & ADC_GCC_GAIN_CAL_MASK);

	GCRa = (uint16_t)((GCCa << 16U) / (0x1FFFFU - GCCa));
	/* Gain_CalA = (131072 / (131072-(ADC_GCC_GAIN_CAL(ADC0->GCC[0])) - 1. */
	GCRb = (uint16_t)((GCCb << 16U) / (0x1FFFFU - GCCb));
	/* Gain_CalB = (131072 / (131072-(ADC_GCC_GAIN_CAL(ADC0->GCC[1])) - 1. */

	ADC0->GCR[0] = ADC_GCR_GCALR(GCRa);
	ADC0->GCR[1] = ADC_GCR_GCALR(GCRb);

	/* Indicate the values are valid. */
	ADC0->GCR[0] |= ADC_GCR_RDY_MASK;
	ADC0->GCR[1] |= ADC_GCR_RDY_MASK;
	while (ADC_STAT_CAL_RDY_MASK != (ADC0->STAT & ADC_STAT_CAL_RDY_MASK))
	{
	}

	/* Init commands */
	/* The available command number are 1-15, while the index of register group are 0-14. */
	/* Configure the CMD 1 */

	ADC0->CMD[0].CMDL = ADC_CMDL_ADCH(3U)  |  /* Channel number (ADC0IN3A (CUR_A) and ADC0IN3B (CUR_C)) */
                            ADC_CMDL_CTYPE(3U) |  /* Conversion type dual single-ended CUR_A, CUR_C */
                            ADC_CMDL_MODE(0U);    /* Resolution of conversion */
	ADC0->CMD[0].CMDH = ADC_CMDH_NEXT(2U);    /* Next command select (CMD2) */

	/* Configure the CMD 2 */
	ADC0->CMD[1].CMDL = ADC_CMDL_ADCH(8U)  |  /* Channel number (ADC0IN8A (CUR_B)) */
                            ADC_CMDL_CTYPE(0U) |  /* Conversion type single-ended */
                            ADC_CMDL_MODE(0U);    /* Resolution of conversion */
	ADC0->CMD[1].CMDH = ADC_CMDH_NEXT(3U);    /* Next command select (not defined) */

	/* Configure the CMD 3 */
	ADC0->CMD[2].CMDL = ADC_CMDL_ADCH(1U)  |  /* Channel number (ADC0IN1A (VLT_DCB)) */
                            ADC_CMDL_CTYPE(0U) |  /* Conversion type single-ended */
                            ADC_CMDL_MODE(0U);    /* Resolution of conversion */
	ADC0->CMD[2].CMDH = ADC_CMDH_NEXT(0U);    /* Next command select (not defined) */


	/* Init triggers (use trigger 0). */
	ADC0->TCTRL[0] = ADC_TCTRL_FIFO_SEL_A(0) |
			ADC_TCTRL_FIFO_SEL_B(1) |
			ADC_TCTRL_TCMD(1U) |     /* Trigger command select */
			ADC_TCTRL_HTEN_MASK;     /* Trigger enable */


	/* Enable TCOMP interrupt. */
	ADC0->IE |= ADC_IE_TCOMP_IE(0xFU);

	NVIC_SetPriority(ADC0_IRQn, 1U);
	NVIC_EnableIRQ(ADC0_IRQn);
}

/*!
  @brief   void InitHsCmp0(void)
            - Initialization of the comparator 0 module for dc-bus over current
              detection to generate eFlexPWM0 fault
  @param   void

  @return  none
*/
void InitHsCmp0(void)
{
	/* Disable power down */
	PMC->PDRUNCFGCLR0 = PMC_PDRUNCFG0_PDEN_VREF_MASK
					  | PMC_PDRUNCFG0_PDEN_HSCMP0_MASK;
	PMC->PDRUNCFGCLR1 = PMC_PDRUNCFG1_PDEN_CMPBIAS_MASK
					  | PMC_PDRUNCFG1_PDEN_HSCMP0_DAC_MASK;

	SYSCON->AHBCLKCTRLSET[3] = SYSCON_AHBCLKCTRL3_HSCMP0_MASK;
	/* Input minus = internal 8-bit DAC, input plus = analog mux in3 (P1_5), high power/high speed mode */
	HSCMP0->CCR2 |= (uint32_t)( HSCMP_CCR2_INMSEL(0) | HSCMP_CCR2_INPSEL(1) | HSCMP_CCR2_MSEL(7U) | HSCMP_CCR2_PSEL(3U) | HSCMP_CCR2_CMP_HPMD_MASK);

	/* Setting for external OPAMP. */
	HSCMP0->DCR = HSCMP_DCR_DAC_DATA(HSCMP_THRESHOLD_CURRENT(7.5F)) |   /* HSCMP current threshold 7.5A. */
			      HSCMP_DCR_DACOE(1)       |   /* DAC output enable */
			      HSCMP_DCR_DAC_HPMD(1)    |   /* High power mode enabled */
			      HSCMP_DCR_DAC_EN(1);         /* DAC enable */

	/* HSCMP enable */
	HSCMP0->CCR0 |= HSCMP_CCR0_CMP_EN_MASK;
}

/*!
 * @brief   void InitSlowLoop(void)
 *           - Initialization of the CTIMER0 peripheral
 *           - performs slow control loop counter
 *
 * @param   void
 *
 * @return  none
 */
void InitSlowLoop(void)
{
    /* Use 96 MHz clock for some of the Ctimer0. */
    SYSCON->CTIMERCLKSEL[0] =  CTIMER_CLK_FRO & SYSCON_CTIMERCLKSEL_SEL_MASK;
    /* Enable Timer0 clock. */
    SYSCON->AHBCLKCTRLSET[1] = SYSCON_AHBCLKCTRL1_TIMER0_MASK;

    /* Enable Timer0 clock reset. */
    
    SYSCON->PRESETCTRLSET[1] = SYSCON_PRESETCTRL1_TIMER0_RST_MASK;             /* Set bit. */

    while (0u == (SYSCON->PRESETCTRL1 & SYSCON_PRESETCTRL1_TIMER0_RST_MASK))   /* Wait until it reads 0b`1 */
    {
    }

    /* Clear Timer0 clock reset. */
    SYSCON->PRESETCTRLCLR[1] = SYSCON_PRESETCTRL1_TIMER0_RST_MASK;             /* Clear bit */
    while (SYSCON_PRESETCTRL1_TIMER0_RST_MASK ==                               /* Wait until it reads 0b0 */
          (SYSCON->PRESETCTRL1 & SYSCON_PRESETCTRL1_TIMER0_RST_MASK))
    {
    }

    /* Configure match control register. */
    CTIMER0->MCR |= CTIMER_MCR_MR0R(1U)  |   /* Enable reset of TC after it matches with MR0. */
                    CTIMER_MCR_MR0I(1U);     /* Enable interrupt generation after TC matches with MR0. */
    
    /* Configure match register. */
    CTIMER0->MR[0] = (CLOCK_GetFreq(kCLOCK_FroHf))  /* Get CTimer0 frequency for correct set Match register value. */
                     / M1_SLOW_LOOP_FREQ;           /* Set slow control loop frequency in Hz. */
    
    /* Configure interrupt register. */
    CTIMER0->IR = CTIMER_IR_MR0INT_MASK;     /* Set interrupt flag for match channel 0. */
    NVIC_SetPriority(CTIMER0_IRQn, 2U);
    NVIC_EnableIRQ(CTIMER0_IRQn);            /* Enable LEVEL1 interrupt and update the call back function. */

    /* Configure timer control register. */
    CTIMER0->TCR |= CTIMER_TCR_CEN_MASK;     /* Start the timer counter. */
}



/*!
 * @brief   void InitInputmux(void)
 *           - Initialization of the Input Multiplexing
 *
 * @param   void
 *
 * @return  none
 */
void InitInputmux(void)
{
    SYSCON->AHBCLKCTRLSET[0] = SYSCON_AHBCLKCTRL0_MUX_MASK;
    INPUTMUX->PWM0_FAULT[0]  = INPUTMUX_PWM0_FAULTN_PWM0_FAULT_TRIGIN(INPUTMUX_SDK_MASK & kINPUTMUX_Hscmp0OutToPwm0FaultTrigger);
    INPUTMUX->ADC0_TRIG[0]   = INPUTMUX_ADC0_TRIGN_ADC0_TRIG_TRIGIN(INPUTMUX_SDK_MASK & kINPUTMUX_Pwm0Sm0MuxTrig0ToAdc0Trigger);
}




