/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "mc_periph_init.h"
#include "peripherals.h"
#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "fsl_power.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/

/*******************************************************************************
 * Typedef
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* Motor 1 */
static void InitADC0(void);
static void InitHsCmp0(void);
static void InitPWM0(void);
static void InitQD0(void);
#if ( defined(USE_INTERNAL_OPAMPS) && (false != USE_INTERNAL_OPAMPS) )
static void InitVref1V625_IOpAmp(void);
static void InitOpAmps_IOpAmp(void);
#endif
/* Motor 2 */
static void InitADC1(void);
static void InitHsCmp1(void);
static void InitPWM1(void);
static void InitQD1(void);

/* Common for motor 1 and motor 2 */
static void InitSlowLoop(void);
static void InitClock(void);
static void InitInputmux(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* configuration structure for 3-phase PWM mc driver */
mcdrv_eflexpwm_t g_sM1Pwm3ph;
mcdrv_eflexpwm_t g_sM2Pwm3ph;

/* structure for current and voltage measurement*/
mcdrv_adc_t g_sM1AdcSensor;
mcdrv_adc_t g_sM2AdcSensor;

/* Structure for Encoder driver */
mcdrv_qd_enc_t g_sM1Enc;
mcdrv_qd_enc_t g_sM2Enc;

/* Clock setup structure */
clock_setup_t g_sClockSetup;

/*******************************************************************************
 * Local functions
 ******************************************************************************/
/*!
 * @brief   void InitPWM0(void)
 *           - Initialization of the eFlexPWM0 peripheral for motor M1
 *           - 3-phase center-aligned PWM
 *
 * @param   void
 *
 * @return  none
 */
static void InitPWM0(void)
{
    PWM_Type *PWMBase = (PWM_Type *)PWM0;

    /*eFlexPWM0 init*/
    SYSCON->PWM0SUBCTL = (SYSCON_PWM0SUBCTL_CLK0_EN_MASK | SYSCON_PWM0SUBCTL_CLK1_EN_MASK | SYSCON_PWM0SUBCTL_CLK2_EN_MASK | SYSCON_PWM0SUBCTL_CLK3_EN_MASK); //Enable Sub-module0 clock
    CLOCK_EnableClock(kCLOCK_Pwm0);

    /* value register initial values, duty cycle 50% */
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

    PWMBase->SM[0].VAL4 = PWM_VAL4_VAL4((uint16_t)((-(M1_PWM_MODULO / 2))));

    /* PWM0 submodule 0 trigger on VAL4 enabled for ADC synchronization */
    PWMBase->SM[0].TCTRL |= PWM_TCTRL_OUT_TRIG_EN(1 << 4);
    /* PWM0 submodule 1 trigger on VAL0 enabled for PWM1 synchronization */
    PWMBase->SM[1].TCTRL |= PWM_TCTRL_OUT_TRIG_EN(1 << 0);

    /* set deadtime (number of Fast Peripheral Clocks)
       DTCNT0,1 = T_dead * f_fpc = 1.5us * 72MHz = 108 */
    /* DTCNTx = 95 if the clock is 95977472 Hz and deadtime = 1 us */
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

    /* Modules one and two gets clock from module zero */
    PWMBase->SM[1].CTRL2 = (PWMBase->SM[1].CTRL2 & ~PWM_CTRL2_CLK_SEL_MASK) | PWM_CTRL2_CLK_SEL(0x2);
    PWMBase->SM[2].CTRL2 = (PWMBase->SM[2].CTRL2 & ~PWM_CTRL2_CLK_SEL_MASK) | PWM_CTRL2_CLK_SEL(0x2);

    /* Master reload active for modules one and two */
    PWMBase->SM[1].CTRL2 |= PWM_CTRL2_RELOAD_SEL_MASK;
    PWMBase->SM[2].CTRL2 |= PWM_CTRL2_RELOAD_SEL_MASK;

    /* Master sync active for modules one and two */
    PWMBase->SM[1].CTRL2 = (PWMBase->SM[1].CTRL2 & ~PWM_CTRL2_INIT_SEL_MASK) | PWM_CTRL2_INIT_SEL(0x2);
    PWMBase->SM[2].CTRL2 = (PWMBase->SM[2].CTRL2 & ~PWM_CTRL2_INIT_SEL_MASK) | PWM_CTRL2_INIT_SEL(0x2);

    /* PWMs are re-enabled at PWM full cycle */
    PWMBase->FSTS = (PWMBase->FSTS & ~PWM_FSTS_FFULL_MASK) | PWM_FSTS_FFULL(0x1);

    /* PWM fault filter - 3 Fast periph. clocks sample rate, 5 agreeing
       samples to activate */
    PWMBase->FFILT = (PWMBase->FFILT & ~PWM_FFILT_FILT_PER_MASK) | PWM_FFILT_FILT_PER(2);

    /* All interrupts disabled, safe manual fault clearing, inversed logic (trigger level = high) */
    PWMBase->FCTRL &= ~(PWM_FCTRL_FLVL_MASK | PWM_FCTRL_FAUTO_MASK | PWM_FCTRL_FSAFE_MASK | PWM_FCTRL_FIE_MASK); /* clear FCTRL register prior further settings */
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

    /* eFlexPWM base address */
    g_sM1Pwm3ph.pui32PwmBaseAddress = (PWM_Type *)PWMBase;
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
static void InitADC0(void)
{
    uint32_t GCCa;
    uint32_t GCCb;
    uint32_t GCRa;
    uint32_t GCRb;

    CLOCK_SetClkDiv(kCLOCK_DivAdc0Clk, 2U, true);
    CLOCK_AttachClk(kFRO_HF_to_ADC0);

    /* Disable VREF power down. */
    POWER_DisablePD(kPDRUNCFG_PD_VREF);

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
#if ( defined(USE_INTERNAL_OPAMPS) && (false != USE_INTERNAL_OPAMPS) )
    ADC0->CMD[0].CMDL = ADC_CMDL_ADCH(0U)  |  /* Channel number (ADC0IN0A (OPAMP0 - CUR_A) and ADC0IN0B (OPAMP1 - CUR_C)) */
#else
    ADC0->CMD[0].CMDL = ADC_CMDL_ADCH(3U)  |  /* Channel number (ADC0IN3A (CUR_A) and ADC0IN3B (CUR_C)) */
#endif
                        ADC_CMDL_CTYPE(3U) |  /* Conversion type dual single-ended CUR_A, CUR_C */
                        ADC_CMDL_MODE(0U);    /* Resolution of conversion */
    ADC0->CMD[0].CMDH = ADC_CMDH_NEXT(2U);    /* Next command select (CMD2) */

    /* Configure the CMD 2 */
#if ( defined(USE_INTERNAL_OPAMPS) && (false != USE_INTERNAL_OPAMPS) )
    ADC0->CMD[1].CMDL = ADC_CMDL_ADCH(2U)  |  /* Channel number (ADC0IN2A (OPAMP2 - CUR_B)) */
                        ADC_CMDL_CTYPE(0U) |  /* Conversion type single-ended */
#else
    ADC0->CMD[1].CMDL = ADC_CMDL_ADCH(8U)  |  /* Channel number (ADC0IN8A (CUR_B)) */
                        ADC_CMDL_CTYPE(0U) |  /* Conversion type single-ended */
#endif
                        ADC_CMDL_MODE(0U);    /* Resolution of conversion */
    ADC0->CMD[1].CMDH = ADC_CMDH_NEXT(3U);    /* Next command select (CMD3) */

    /* Configure the CMD 3 */
    ADC0->CMD[2].CMDL = ADC_CMDL_ADCH(1U)  |  /* Channel number (ADC0IN1A (VLT_DCB)) */
                        ADC_CMDL_CTYPE(0U) |  /* Conversion type */
                        ADC_CMDL_MODE(0U);    /* Resolution of conversion */
    ADC0->CMD[2].CMDH = ADC_CMDH_NEXT(0U);    /* Next command select (not defined) */

    /* Init triggers (use trigger 0). */
    ADC0->TCTRL[0] = ADC_TCTRL_FIFO_SEL_A(0) | /* Channels A stored to FIFO 0 */
                     ADC_TCTRL_FIFO_SEL_B(1) | /* Channels B stored to FIFO 1 - only used in dual single-ended mode (in single-ended mode, channels B stored to FIFO 0). */
                     ADC_TCTRL_TCMD(1U) |      /* Trigger command select */
                     ADC_TCTRL_HTEN_MASK;      /* Trigger enable */

    /* ADC base address */
    g_sM1AdcSensor.pToAdcBase = (ADC_Type *)ADC0;

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
static void InitHsCmp0(void)
{
    /* Disable power down */
    POWER_DisablePD(kPDRUNCFG_PD_HSCMP0);
    POWER_DisablePD(kPDRUNCFG_PD_VREF);
    POWER_DisablePD(kPDRUNCFG_PD_CMPBIAS);
    POWER_DisablePD(kPDRUNCFG_PD_HSCMP0_DAC);

    CLOCK_EnableClock(kCLOCK_Hscmp0);

    /* Input minus = internal 8-bit DAC, input plus = analog mux in3 (P1_5), high power/high speed mode */
    HSCMP0->CCR2 |= (uint32_t)( HSCMP_CCR2_INMSEL(0) | HSCMP_CCR2_INPSEL(1) | HSCMP_CCR2_MSEL(7U) | HSCMP_CCR2_PSEL(3U) | HSCMP_CCR2_CMP_HPMD_MASK);

    /* Setting for external OPAMP: Set DAC_OUT to 3.15V (7.5A overcurrent through 0.02 Ohm shunt, gain 10x). */
    HSCMP0->DCR = HSCMP_DCR_DAC_DATA(243) |   /* (3.3V / 256) * (243 + 1) = 3.145 V */
                  HSCMP_DCR_DACOE(1)      |   /* DAC output enable */
                  HSCMP_DCR_DAC_HPMD(1)   |   /* High power mode enabled */
                  HSCMP_DCR_DAC_EN(1);        /* DAC enable */

    /* HSCMP enable */
    HSCMP0->CCR0 |= HSCMP_CCR0_CMP_EN_MASK;
}

/*!
 * @brief   void InitQD0(void)
 *           - Initialization of the Quadrature Encoder 0 peripheral
 *           - performs speed and position sensor processing
 *
 * @param   void
 *
 * @return  none
 */
static void InitQD0(void)
{
    /* Enable clock to ENC modules */
    CLOCK_EnableClock(kCLOCK_Enc0);

    /* Pass initialization data into encoder driver structure */
    /* encoder position and speed measurement */
    g_sM1Enc.pui32QdBase   = (ENC_Type *)ENC0;
    g_sM1Enc.sTo.fltPGain  = M1_POSPE_TO_KP_GAIN;
    g_sM1Enc.sTo.fltIGain  = M1_POSPE_TO_KI_GAIN;
    g_sM1Enc.sTo.fltThGain = M1_POSPE_TO_THETA_GAIN;
    g_sM1Enc.a32PosMeGain  = M1_POSPE_MECH_POS_GAIN;
    g_sM1Enc.ui16Pp        = M1_MOTOR_PP;
    g_sM1Enc.bDirection    = M1_POSPE_ENC_DIRECTION;
    g_sM1Enc.fltSpdEncMin  = M1_POSPE_ENC_N_MIN;
    g_sM1Enc.ui16PulseNumber = M1_POSPE_ENC_PULSES;
    MCDRV_QdEncSetDirection(&g_sM1Enc);

    /* Initialization modulo counter */
    MCDRV_QdEncSetPulses(&g_sM1Enc);

    /* Enable modulo counting and revolution counter increment on roll-over */
    ENC0->CTRL2 = (ENC_CTRL2_MOD_MASK | ENC_CTRL2_REVMOD_MASK);
}

#if ( defined(USE_INTERNAL_OPAMPS) && (false != USE_INTERNAL_OPAMPS) )
/*!
 * @brief   void InitVref1V625_IOpAmp(void)
 *           - Initialization of the Voltage Reference peripheral
 *
 * @param   void
 *
 * @return  none
 */
static void InitVref1V625_IOpAmp(void)
{
    //Enable power VREF
    PMC->PDRUNCFGCLR0 = PMC_PDRUNCFG0_PDEN_VREF_MASK;
    CLOCK_EnableClock(kCLOCK_Vref);

    /* Trim 1.0 V to 1.625 V */
    VREF->UTRIM |= ( (0x3FU << 8U) |  0x06U ) ;

    VREF->CSR |= VREF_CSR_BUF21EN_MASK |
                VREF_CSR_LPBG_BUF_EN_MASK |
                VREF_CSR_CHOPEN_MASK |
                VREF_CSR_ICOMPEN_MASK |
                VREF_CSR_HI_PWR_LV_MASK |
                VREF_CSR_REGEN_MASK |
                VREF_CSR_LPBGEN_MASK |
                VREF_CSR_HCBGEN_MASK;  /* enable VREF_OUT */
}

/*!
 * @brief   void InitOpAmps_IOpAmp(void)
 *           - Initialization of the Operational Amplifier 0-2 peripheral
 *
 * @param   void
 *
 * @return  none
 */
static void InitOpAmps_IOpAmp(void)
{
    /* Enable clock. */
    SYSCON->AHBCLKCTRL3 |= SYSCON_AHBCLKCTRL3_OPAMP0_MASK  |  /* Enables the clock for OPAMP0 */
                           SYSCON_AHBCLKCTRL3_OPAMP1_MASK  |  /* Enables the clock for OPAMP1 */
                           SYSCON_AHBCLKCTRL3_OPAMP2_MASK;    /* Enables the clock for OPAMP2 */

    /* Disable OPAMP0, OPAMP1 and OPAMP2 power down. */
    POWER_DisablePD(kPDRUNCFG_PD_OPAMP0);
    POWER_DisablePD(kPDRUNCFG_PD_OPAMP1);
    POWER_DisablePD(kPDRUNCFG_PD_OPAMP2);

    /* Operational amplifier 0 OPAMP_CTR register configuration. */
    OPAMP0->OPAMP_CTR |= OPAMP_OPAMP_CTR_EN(1U)     |   /* Enable operational amplifier 0 */
                         OPAMP_OPAMP_CTR_INTREF(0U) |   /* Internal reference voltage selected as Vdda/2. */
                         OPAMP_OPAMP_CTR_PREF(2U)   |   /* Positive part reference voltage select Vrefh1,
                                                           connected from voltage reference output.       */
                         OPAMP_OPAMP_CTR_PGAIN(4U)  |   /* Selected 1:8 positive programmable gain ratio. */
                         OPAMP_OPAMP_CTR_NGAIN(4U);     /* Selected 1:8 negative programmable gain ratio. */

    /* Operational amplifier 1 OPAMP_CTR register configuration. */
    OPAMP1->OPAMP_CTR |= OPAMP_OPAMP_CTR_EN(1U)     |   /* Enable operational amplifier 1 */
                         OPAMP_OPAMP_CTR_INTREF(0U) |   /* Internal reference voltage selected as Vdda/2. */
                         OPAMP_OPAMP_CTR_PREF(2U)   |   /* Positive part reference voltage select Vrefh1,
                                                           connected from voltage reference output.       */
                         OPAMP_OPAMP_CTR_PGAIN(4U)  |   /* Selected 1:8 positive programmable gain ratio. */
                         OPAMP_OPAMP_CTR_NGAIN(4U);     /* Selected 1:8 negative programmable gain ratio. */

    /* Operational amplifier 2 OPAMP_CTR register configuration. */
    OPAMP2->OPAMP_CTR |= OPAMP_OPAMP_CTR_EN(1U)     |   /* Enable operational amplifier 2 */
                         OPAMP_OPAMP_CTR_INTREF(0U) |   /* Internal reference voltage selected as Vdda/2. */
                         OPAMP_OPAMP_CTR_PREF(2U)   |   /* Positive part reference voltage select Vrefh1,
                                                           connected from voltage reference output.       */
                         OPAMP_OPAMP_CTR_PGAIN(4U)  |   /* Selected 1:8 positive programmable gain ratio. */
                         OPAMP_OPAMP_CTR_NGAIN(4U);     /* Selected 1:8 negative programmable gain ratio. */
}
#endif /* end of USE_INTERNAL_OPAMPS */

/*!
 * @brief   void InitPWM1(void)
 *           - Initialization of the eFlexPWM1 peripheral for motor M1
 *           - 3-phase center-aligned PWM
 *
 * @param   void
 *
 * @return  none
 */
static void InitPWM1(void)
{
    PWM_Type *PWMBase = (PWM_Type *)PWM1;

    /* eFlexPWM1 init */
    SYSCON->PWM1SUBCTL = (SYSCON_PWM1SUBCTL_CLK0_EN_MASK | SYSCON_PWM1SUBCTL_CLK1_EN_MASK | SYSCON_PWM1SUBCTL_CLK2_EN_MASK | SYSCON_PWM1SUBCTL_CLK3_EN_MASK); //Enable Sub-module0 clock
    CLOCK_EnableClock(kCLOCK_Pwm1);

    /* value register initial values, duty cycle 50% */
    PWMBase->SM[0].INIT = PWM_INIT_INIT((uint16_t)(-(M2_PWM_MODULO / 2)));
    PWMBase->SM[1].INIT = PWM_INIT_INIT((uint16_t)(-(M2_PWM_MODULO / 2)));
    PWMBase->SM[2].INIT = PWM_INIT_INIT((uint16_t)(-(M2_PWM_MODULO / 2)));
    PWMBase->SM[3].INIT = PWM_INIT_INIT((uint16_t)(-(M2_PWM_MODULO / 2)));

    PWMBase->SM[0].VAL1 = PWM_VAL1_VAL1((uint16_t)((M2_PWM_MODULO / 2) - 1));
    PWMBase->SM[1].VAL1 = PWM_VAL1_VAL1((uint16_t)((M2_PWM_MODULO / 2) - 1));
    PWMBase->SM[2].VAL1 = PWM_VAL1_VAL1((uint16_t)((M2_PWM_MODULO / 2) - 1));
    PWMBase->SM[3].VAL1 = PWM_VAL1_VAL1((uint16_t)((M2_PWM_MODULO / 2) - 1));

    PWMBase->SM[0].VAL2 = 0;
    PWMBase->SM[1].VAL2 = 0;
    PWMBase->SM[2].VAL2 = 0;
    PWMBase->SM[3].VAL2 = 0;

    PWMBase->SM[0].VAL3 = 0;
    PWMBase->SM[1].VAL3 = 0;
    PWMBase->SM[2].VAL3 = 0;
    PWMBase->SM[3].VAL3 = 0;

    PWMBase->SM[0].VAL4 = PWM_VAL4_VAL4((uint16_t)((-(M2_PWM_MODULO / 2))));

    /* PWM1 module 0 trigger on VAL4 enabled for ADC synchronization */
    PWMBase->SM[0].TCTRL |= PWM_TCTRL_OUT_TRIG_EN(1 << 4);

    /* set deadtime (number of Fast Peripheral Clocks)
       DTCNT0,1 = T_dead * f_fpc = 1.5us * 72MHz = 108 */
    /* DTCNTx = 95 if the clock is 95977472 Hz and deadtime = 1 us */
    PWMBase->SM[0].DTCNT0 = ((M2_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
    PWMBase->SM[1].DTCNT0 = ((M2_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
    PWMBase->SM[2].DTCNT0 = ((M2_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
    PWMBase->SM[3].DTCNT0 = ((M2_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
    PWMBase->SM[0].DTCNT1 = ((M2_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
    PWMBase->SM[1].DTCNT1 = ((M2_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
    PWMBase->SM[2].DTCNT1 = ((M2_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);
    PWMBase->SM[3].DTCNT1 = ((M2_PWM_DEADTIME * (MCU_CLOCK_FREQ / 1000000U)) / 1000U);

     /* Full cycle reload */
    PWMBase->SM[0].CTRL |= PWM_CTRL_FULL_MASK;
    PWMBase->SM[1].CTRL |= PWM_CTRL_FULL_MASK;
    PWMBase->SM[2].CTRL |= PWM_CTRL_FULL_MASK;
    PWMBase->SM[3].CTRL |= PWM_CTRL_FULL_MASK;

    /* Fault0 (HSCMP1_OUT) trigger */
    PWMBase->SM[0].DISMAP[0] = 0xF111U;
    PWMBase->SM[1].DISMAP[0] = 0xF111U;
    PWMBase->SM[2].DISMAP[0] = 0xF111U;
    PWMBase->SM[3].DISMAP[0] = 0xF111U;

    /* Modules one and two gets clock from module zero */
    PWMBase->SM[1].CTRL2 = (PWMBase->SM[1].CTRL2 & ~PWM_CTRL2_CLK_SEL_MASK) | PWM_CTRL2_CLK_SEL(0x2);
    PWMBase->SM[2].CTRL2 = (PWMBase->SM[2].CTRL2 & ~PWM_CTRL2_CLK_SEL_MASK) | PWM_CTRL2_CLK_SEL(0x2);

    /* Master reload active for modules one and two */
    PWMBase->SM[1].CTRL2 |= PWM_CTRL2_RELOAD_SEL_MASK;
    PWMBase->SM[2].CTRL2 |= PWM_CTRL2_RELOAD_SEL_MASK;

    /* Master sync active for modules one and two */
    PWMBase->SM[1].CTRL2 = (PWMBase->SM[1].CTRL2 & ~PWM_CTRL2_INIT_SEL_MASK) | PWM_CTRL2_INIT_SEL(0x2);
    PWMBase->SM[2].CTRL2 = (PWMBase->SM[2].CTRL2 & ~PWM_CTRL2_INIT_SEL_MASK) | PWM_CTRL2_INIT_SEL(0x2);

    /* External synchronization for submodule 0 from PWM0 */
    PWMBase->SM[0].CTRL2 = (PWMBase->SM[0].CTRL2 & ~PWM_CTRL2_INIT_SEL_MASK) | PWM_CTRL2_INIT_SEL(0x3);

    /* PWMs are re-enabled at PWM full cycle */
    PWMBase->FSTS = (PWMBase->FSTS & ~PWM_FSTS_FFULL_MASK) | PWM_FSTS_FFULL(0x1);

    /* PWM fault filter - 3 Fast periph. clocks sample rate, 5 agreeing
       samples to activate */
    PWMBase->FFILT = (PWMBase->FFILT & ~PWM_FFILT_FILT_PER_MASK) | PWM_FFILT_FILT_PER(2);

    /* All interrupts disabled, safe manual fault clearing, inversed logic (trigger level = high) */
    PWMBase->FCTRL &= ~(PWM_FCTRL_FLVL_MASK | PWM_FCTRL_FAUTO_MASK | PWM_FCTRL_FSAFE_MASK | PWM_FCTRL_FIE_MASK); /* clear FCTRL register prior further settings */
    PWMBase->FCTRL |= PWM_FCTRL_FIE(0U); /* FAULT 0 & FAULT 1 - Interrupt disable */
    PWMBase->FCTRL |= PWM_FCTRL_FLVL(0xFU);
    PWMBase->FCTRL |= PWM_FCTRL_FAUTO(0U);
    PWMBase->FCTRL |= PWM_FCTRL_FSAFE(0xFU);

    /* Clear all fault flags */
    PWMBase->FSTS = (PWMBase->FSTS & ~PWM_FSTS_FFLAG_MASK) | PWM_FSTS_FFLAG(0xF);

    /* Start PWMs (set load OK flags and run - we need to trigger the ADC) */
    PWMBase->MCTRL = (PWMBase->MCTRL & ~PWM_MCTRL_CLDOK_MASK) | PWM_MCTRL_CLDOK(0xF);
    PWMBase->MCTRL = (PWMBase->MCTRL & ~PWM_MCTRL_LDOK_MASK) | PWM_MCTRL_LDOK(0xF);
    PWMBase->MCTRL = (PWMBase->MCTRL & ~PWM_MCTRL_RUN_MASK) | PWM_MCTRL_RUN(0xF);

    /* eFlexPWM base address */
    g_sM2Pwm3ph.pui32PwmBaseAddress = (PWM_Type *)PWMBase;
}

/*!
 * @brief   void InitADC1(void)
 *           - Initialization of the ADC1 peripheral
 *           - Initialization of the A/D converter for current and voltage sensing
 *
 * @param   void
 *
 * @return  none
 */
static void InitADC1(void)
{
    uint32_t GCCa;
    uint32_t GCCb;
    uint32_t GCRa;
    uint32_t GCRb;

    CLOCK_SetClkDiv(kCLOCK_DivAdc1Clk, 2U, true);
    CLOCK_AttachClk(kFRO_HF_to_ADC1);

    /* Disable VREF power down */
    POWER_DisablePD(kPDRUNCFG_PD_VREF);

    /* Init ADC */
    /* Enable the clock. */
    SYSCON->AHBCLKCTRL0 |= SYSCON_AHBCLKCTRL0_ADC1_MASK;

    /* Reset the module. */
    ADC1->CTRL |= ADC_CTRL_RST_MASK;          /* ADC logic reset */
    ADC1->CTRL &= ~ADC_CTRL_RST_MASK;
    ADC1->CTRL |= ADC_CTRL_RSTFIFO0_MASK;     /* Reset FIFO 0 */
    ADC1->CTRL |= ADC_CTRL_RSTFIFO1_MASK;     /* Reset FIFO 1 */

    /* Disable the module before setting configuration. */
    ADC1->CTRL &= ~ADC_CTRL_ADCEN_MASK;

    /* Configure the module generally. */
    ADC1->CTRL &= ~ADC_CTRL_DOZEN_MASK;

    /* Set calibration average mode. */
    ADC1->CTRL = ADC_CTRL_CAL_AVGS(7U);

    /* ADC1 configuration. */
    ADC1->CFG |= ADC_CFG_PWREN_MASK  |  /* ADC analog circuits pre-enable */
                 ADC_CFG_PUDLY(0x80) |  /* Power up delay */
                 ADC_CFG_REFSEL(2U)  |  /* Reference voltage */
                 ADC_CFG_PWRSEL(3U);    /* Power configuration */


    /* Enable the module after setting configuration. */
    ADC1->CTRL |= ADC_CTRL_ADCEN_MASK;

    /* Offset calibration. */
    ADC1->CTRL |= ADC_CTRL_CALOFS_MASK;
    while (ADC_STAT_CAL_RDY_MASK != (ADC1->STAT & ADC_STAT_CAL_RDY_MASK))
    {
    }

    /* AutoCalibration */
    assert((0u == ((ADC_FCTRL_FCOUNT_MASK & ADC1->FCTRL[0]) >> ADC_FCTRL_FCOUNT_SHIFT))
        && (0u == ((ADC_FCTRL_FCOUNT_MASK & ADC1->FCTRL[1]) >> ADC_FCTRL_FCOUNT_SHIFT)));

    /* Request gain calibration. */
    ADC1->CTRL |= ADC_CTRL_CAL_REQ_MASK;
    while ((ADC_GCC_RDY_MASK != (ADC1->GCC[0] & ADC_GCC_RDY_MASK)) ||
           (ADC_GCC_RDY_MASK != (ADC1->GCC[1] & ADC_GCC_RDY_MASK)))
    {
    }

    /* Calculate gain offset. */
    GCCa = (ADC1->GCC[0] & ADC_GCC_GAIN_CAL_MASK);
    GCCb = (ADC1->GCC[1] & ADC_GCC_GAIN_CAL_MASK);

    GCRa = (uint16_t)((GCCa << 16U) / (0x1FFFFU - GCCa));
    /* Gain_CalA = (131072 / (131072-(ADC_GCC_GAIN_CAL(ADC1->GCC[0])) - 1. */
    GCRb = (uint16_t)((GCCb << 16U) / (0x1FFFFU - GCCb));
    /* Gain_CalB = (131072 / (131072-(ADC_GCC_GAIN_CAL(ADC1->GCC[1])) - 1. */

    ADC1->GCR[0] = ADC_GCR_GCALR(GCRa);
    ADC1->GCR[1] = ADC_GCR_GCALR(GCRb);

    /* Indicate the values are valid. */
    ADC1->GCR[0] |= ADC_GCR_RDY_MASK;
    ADC1->GCR[1] |= ADC_GCR_RDY_MASK;
    while (ADC_STAT_CAL_RDY_MASK != (ADC1->STAT & ADC_STAT_CAL_RDY_MASK))
    {
    }

    /* Init commands */
    /* The available command number are 1-15, while the index of register group are 0-14. */
    /* Configure the CMD 1 */
    ADC1->CMD[0].CMDL = ADC_CMDL_ADCH(3U)  |  /* Channel number (ADC1IN3A (CUR_A) and ADC1IN3B (CUR_C)) */
                        ADC_CMDL_CTYPE(3U) |  /* Conversion type dual single-ended CUR_A, CUR_C */
                        ADC_CMDL_MODE(0U);    /* Resolution of conversion */
    ADC1->CMD[0].CMDH = ADC_CMDH_NEXT(2U);    /* Next command select (CMD2) */

    /* Configure the CMD 2 */
    ADC1->CMD[1].CMDL = ADC_CMDL_ADCH(2U)  |  /* Channel number (ADC1IN2A (CUR_B)) */
                        ADC_CMDL_CTYPE(0U) |  /* Conversion type single-ended */
                        ADC_CMDL_MODE(0U);    /* Resolution of conversion */
    ADC1->CMD[1].CMDH = ADC_CMDH_NEXT(3U);    /* Next command select (CMD3) */

    /* Configure the CMD 3 */
    ADC1->CMD[2].CMDL = ADC_CMDL_ADCH(1U)  |  /* Channel number (ADC1IN1B (VLT_DCB)) */
                        ADC_CMDL_CTYPE(1U) |  /* Conversion type single-ended */
                        ADC_CMDL_MODE(0U);    /* Resolution of conversion */
    ADC1->CMD[2].CMDH = ADC_CMDH_NEXT(0U);    /* Next command select (not defined) */

    /* Init triggers (use trigger 0). */
    ADC1->TCTRL[0] = ADC_TCTRL_FIFO_SEL_A(0) | /* Channels A stored to FIFO 0 */
                     ADC_TCTRL_FIFO_SEL_B(1) | /* Channels B stored to FIFO 1 - only used in dual single-ended mode (in single-ended mode, channels B stored to FIFO 0). */
                     ADC_TCTRL_TCMD(1U) |      /* Trigger command select */
                     ADC_TCTRL_HTEN_MASK;      /* Trigger enable */

    /* ADC base address */
    g_sM2AdcSensor.pToAdcBase = (ADC_Type *)ADC1;

    /* Enable TCOMP interrupt. */
    ADC1->IE |= ADC_IE_TCOMP_IE(0xFU);

    NVIC_SetPriority(ADC1_IRQn, 1U);
    NVIC_EnableIRQ(ADC1_IRQn);
}

/*!
@brief   void InitHsCmp1(void)
          - Initialization of the comparator 1 module for dc-bus over current
            detection to generate eFlexPWM1 fault

@param   void

@return  none
*/
static void InitHsCmp1(void)
{
    /* Disable power down */
    POWER_DisablePD(kPDRUNCFG_PD_HSCMP1);
    POWER_DisablePD(kPDRUNCFG_PD_VREF);
    POWER_DisablePD(kPDRUNCFG_PD_CMPBIAS);
    POWER_DisablePD(kPDRUNCFG_PD_HSCMP1_DAC);

    CLOCK_EnableClock(kCLOCK_Hscmp1);

    /* Input minus = internal 8-bit DAC, input plus = analog mux in3 (P1_5), high power/high speed mode */
    HSCMP1->CCR2 |= (uint32_t)( HSCMP_CCR2_INMSEL(0) | HSCMP_CCR2_INPSEL(1) | HSCMP_CCR2_MSEL(7U) | HSCMP_CCR2_PSEL(3U) | HSCMP_CCR2_CMP_HPMD_MASK);

    /* Setting for external OPAMP: Set DAC_OUT to 3.15V (7.5A overcurrent through 0.02 Ohm shunt, gain 10x). */
    HSCMP1->DCR = HSCMP_DCR_DAC_DATA(243) |   /* (3.3V / 256) * (243 + 1) = 3.145 V */
                  HSCMP_DCR_DACOE(1)      |   /* DAC output enable */
                  HSCMP_DCR_DAC_HPMD(1)   |   /* High power mode enabled */
                  HSCMP_DCR_DAC_EN(1);        /* DAC enable */

    /* HSCMP enable */
    HSCMP1->CCR0 |= HSCMP_CCR0_CMP_EN_MASK;
}

/*!
 * @brief   void InitQD1(void)
 *           - Initialization of the Quadrature Encoder 1 peripheral
 *           - performs speed and position sensor processing
 *
 * @param   void
 *
 * @return  none
 */
static void InitQD1(void)
{
    /* Enable clock to ENC modules */
    CLOCK_EnableClock(kCLOCK_Enc1);

    /* Pass initialization data into encoder driver structure */
    /* encoder position and speed measurement */
    g_sM2Enc.pui32QdBase   = (ENC_Type *)ENC1;
    g_sM2Enc.sTo.fltPGain  = M2_POSPE_TO_KP_GAIN;
    g_sM2Enc.sTo.fltIGain  = M2_POSPE_TO_KI_GAIN;
    g_sM2Enc.sTo.fltThGain = M2_POSPE_TO_THETA_GAIN;
    g_sM2Enc.a32PosMeGain  = M2_POSPE_MECH_POS_GAIN;
    g_sM2Enc.ui16Pp        = M2_MOTOR_PP;
    g_sM2Enc.bDirection    = M2_POSPE_ENC_DIRECTION;
    g_sM2Enc.fltSpdEncMin  = M2_POSPE_ENC_N_MIN;
    g_sM2Enc.ui16PulseNumber = M2_POSPE_ENC_PULSES;
    MCDRV_QdEncSetDirection(&g_sM2Enc);

    /* Initialization modulo counter */
    MCDRV_QdEncSetPulses(&g_sM2Enc);

    /* Enable modulo counting and revolution counter increment on roll-over */
    ENC1->CTRL2 = (ENC_CTRL2_MOD_MASK | ENC_CTRL2_REVMOD_MASK);
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
static void InitSlowLoop(void)
{
    /* Use 96 MHz clock for some of the Ctimer0. */
    CLOCK_AttachClk(kFRO_HF_to_CTIMER0);

    /* Enable Timer0 clock. */
    SYSCON->AHBCLKCTRLSET[1] = SYSCON_AHBCLKCTRL1_TIMER0_MASK;

    /* Enable Timer0 clock reset. */
    SYSCON->PRESETCTRLSET[1] = SYSCON_PRESETCTRL1_TIMER0_RST_MASK;             /* Set bit */
    while (0u == (SYSCON->PRESETCTRL1 & SYSCON_PRESETCTRL1_TIMER0_RST_MASK))   /* Wait until it reads 0b1 */
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
    NVIC_SetPriority(CTIMER0_IRQn, 2U);      /* Set priority lower that ADC IRQ priority */
    NVIC_EnableIRQ(CTIMER0_IRQn);            /* Enable LEVEL1 interrupt and update the call back function. */

    /* Confugurate timer control register. */
    CTIMER0->TCR |= CTIMER_TCR_CEN_MASK;     /* Start the timer counter. */
}

/*!
* @brief   void InitClock(void)
*          - Core, bus, flash clock setup
*
* @param   void
*
* @return  none
*/
static void InitClock(void)
{
    uint32_t ui32CyclesNumber = 0U;

    /* Calculate clock dependant variables for PMSM control algorithm */
    g_sClockSetup.ui32FastPeripheralClock = CLOCK_GetFreq(kCLOCK_CoreSysClk);
    g_sClockSetup.ui32CpuFrequency = CLOCK_GetFreq(kCLOCK_CoreSysClk);

    /* Parameters for motor 1 */
    g_sClockSetup.ui16M1PwmFreq   = M1_PWM_FREQ; /* 10 kHz */
    g_sClockSetup.ui16M1PwmModulo = (g_sClockSetup.ui32FastPeripheralClock) / g_sClockSetup.ui16M1PwmFreq;
    ui32CyclesNumber = ((M1_PWM_DEADTIME * (g_sClockSetup.ui32FastPeripheralClock / 1000000U)) / 1000U);
    g_sClockSetup.ui16M1PwmDeadTime   = ui32CyclesNumber;
    g_sClockSetup.ui16M1SpeedLoopFreq = M1_SLOW_LOOP_FREQ; /* 1kHz */

    /* Parameters for motor 2 */
    g_sClockSetup.ui16M2PwmFreq   = M2_PWM_FREQ; /* 10 kHz */
    g_sClockSetup.ui16M2PwmModulo = (g_sClockSetup.ui32FastPeripheralClock) / g_sClockSetup.ui16M2PwmFreq;
    ui32CyclesNumber = ((M2_PWM_DEADTIME * (g_sClockSetup.ui32FastPeripheralClock / 1000000U)) / 1000U);
    g_sClockSetup.ui16M2PwmDeadTime   = ui32CyclesNumber;
    g_sClockSetup.ui16M2SpeedLoopFreq = M2_SLOW_LOOP_FREQ; /* 1kHz */
}

/*!
 * @brief   void InitInputmux(void)
 *           - Initialization of the Input Multiplexing
 *
 * @param   void
 *
 * @return  none
 */
static void InitInputmux(void)
{
    CLOCK_EnableClock(kCLOCK_InputMux);

    /* Motor connector 1 - HSCMP0 is connected to Freedom board's DCB current sensing OpAmp output */
    INPUTMUX->PWM0_FAULT[0] = 21U;      /* Route HSCMP0_OUT to PWM0 fault 0*/
    INPUTMUX->ADC0_TRIG[0] = 24U;       /* ADC0 trigger 0 = PWM0_SM0_MUX_TRIG0 */

    /* Motor connector 2 - HSCMP1 is connected to Freedom board's DCB current sensing OpAmp output */
    INPUTMUX->PWM1_FAULT[0] = 22U;      /* Route HSCMP1_OUT to PWM1 fault 0*/
    INPUTMUX->ADC1_TRIG[0] = 32U;       /* ADC1 trigger 0 = PWM1_SM0_MUX_TRIG0 */

    /* Common for motor 1 and motor 2 - PWM synchronization */
    INPUTMUX->PWM1_EXTSYNC[0] = INPUTMUX_PWM1_EXTSYNCN_PWM1_EXTSYNC_TRIGIN(26U);
}

/*******************************************************************************
 * Public functions
 ******************************************************************************/
/*!
 * @brief   void MCDRV_Init(void)
 *           - Motor control driver main initialization
 *           - Calls initialization functions of peripherals required for motor
 *             control functionality
 *
 * @param   void
 *
 * @return  none
 */
void MCDRV_Init(void)
{
    InitClock();                /* Init application clock dependent variables */
    InitSlowLoop();             /* Init slow loop counter */
    InitInputmux();             /* Init signal multiplexing */

    /* Motor 1 */
    InitADC0();                 /* Init ADC0 */
    InitHsCmp0();               /* Init High Speed Comparator 0 */
#if( defined(USE_INTERNAL_OPAMPS) && (false != USE_INTERNAL_OPAMPS) )
    InitVref1V625_IOpAmp();     /* Init the 1.625V ref. source */
    InitOpAmps_IOpAmp();        /* Init OPAMS */
#endif
    InitPWM0();                 /* 6-channel PWM0 peripheral init */
    InitQD0();                  /* Qudrature decoder 0 peripheral init */

    /* Motor 2 */
    InitADC1();                 /* Init ADC1 */
    InitHsCmp1();               /* Init High Speed Comparator 1 */
    InitPWM1();                 /* 6-channel PWM1 peripheral init */
    InitQD1();                  /* Qudrature decoder 1 peripheral init */
}
