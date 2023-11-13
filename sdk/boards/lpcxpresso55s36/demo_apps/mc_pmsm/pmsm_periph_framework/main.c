/*
 * Copyright 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "main.h"
#include "mc_periph_init.h"
#include "freemaster.h"

#include "clock_config.h"
#include "pin_mux.h"
#include "fsl_usart.h"
#include "freemaster_serial_usart.h"
#include "mlib_FP.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Enable PWM outputs */
#define PWM_EN(x)        (x->OUTEN |= (PWM_OUTEN_PWMA_EN(0xF) | PWM_OUTEN_PWMB_EN(0xF)))
/* Disable PWM outputs */
#define PWM_DIS(x)       (x->OUTEN &= ~(PWM_OUTEN_PWMA_EN(0xF) | PWM_OUTEN_PWMB_EN(0xF)))


/*******************************************************************************
 * Variables
 ******************************************************************************/
uint32_t ui32Ctimer0IsrCnt = 0;
uint32_t ui32ADC0IsrCnt = 0;

uint16_t ui16IA = 0;
uint16_t ui16IB = 0;
uint16_t ui16IC = 0;
uint16_t ui16UBus = 0;
frac16_t f16DutyA = FRAC16(0.1F);
frac16_t f16DutyB = FRAC16(0.5F);
frac16_t f16DutyC = FRAC16(0.9F);

volatile frac16_t f16UDcBus;
volatile float fltDcBusVoltageScale;

static bool_t bOverCurrent;

static FMSTR_U8 FreeMASTER_RecBuffer0[2048];

FMSTR_REC_BUFF FreeMASTER_Recorder_0 =
{
  .name = "Description of recorder 0",
  .addr = (FMSTR_ADDR)FreeMASTER_RecBuffer0,
  .size = sizeof(FreeMASTER_RecBuffer0),
  .basePeriod_ns = 100000UL
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void InitUSART0(void);
static void InitFreeMASTER(void);
static void UpdatePWM(frac16_t f16PhA, frac16_t f16PhB, frac16_t f16PhC, PWM_Type *pPWMBase);
static bool_t OverCurrentFault(PWM_Type *pPWMBase);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief   Application main function processing peripheral function calling and
 *          infinite loop
 *
 * @param   void
 *
 * @return  none
 */
int main(void)
{
    uint32_t ui32PrimaskReg;

    /* Disable all interrupts before peripherals are initialized */
    ui32PrimaskReg = DisableGlobalIRQ();

    BOARD_BootClockPLL150M();

    InitPins();			/* Init pin mux, gpios */
    InitSlowLoop();             /* Init slow loop timer */
    InitInputmux();             /* Init signal multiplexing */
    InitADC0();                 /* Init ADC0 */
    InitHsCmp0();               /* Init High Speed Comparator 0 */
    InitPWM0();                 /* 6-channel PWM0 peripheral init */
    InitUSART0();               /* FreeMASTER communication layer initialization */

    InitFreeMASTER();           /* FreeMASTER middleware initialization */

    /* Enable PWM outputs */
    PWM_EN(PWM0);

    /* Initialize here to prevent optimization */
    f16UDcBus = FRAC16(0.0);
    fltDcBusVoltageScale = U_DCB_MAX_SCALE;

    /* Enable interrupts  */
    EnableGlobalIRQ(ui32PrimaskReg);

    /* Infinite loop */
    while (1)
    {
        /* FreeMASTER Polling function */
        FMSTR_Poll();
    }
}


/*!
 * @brief   Slow loop interrupt handler (1ms period)
 *           - motor M1 slow application machine function
 *
 * @param   void
 *
 * @return  none
 */
void CTIMER0_IRQHandler(void)
{
    /* Isr check counter */
    ui32Ctimer0IsrCnt++;
    /* Clear the match interrupt flag. */
    CTIMER0->IR |= CTIMER_IR_MR0INT(1U);
    /* Add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
}

/*!
 * @brief   Fast loop interrupt handler (100us period)
 *           - e.g. motor M1 fast application machine function
 *
 * @param   void
 *
 * @return  none
 */
void ADC0_IRQHandler(void)
{
    uint32_t ui32ADCRes;
    uint16_t ui16Data;

    /* Isr check counter */
    ui32ADC0IsrCnt++;
    /* Clear the TCOMP INT flag */
    ADC0->STAT |= ADC_STAT_TCOMP_INT_MASK;

    /* Over current fault detection */
    bOverCurrent = OverCurrentFault(PWM0);

    if(bOverCurrent > 0U)
    {
      /* Disable PWM outputs */
      PWM_DIS(PWM0);
    }
    else
    {
      /* Enable PWM outputs */
      PWM_EN(PWM0);
    }

    /* Call FreeMASTER recorder */
    FMSTR_Recorder(0);

    /* Read and store command 1 result from ADC channel A */
    ui32ADCRes = ADC0->RESFIFO[0];
    ui16Data = (uint16_t)(ui32ADCRes & ADC_RESFIFO_D_MASK);
    ui16IA = ui16Data << 1U;            /* Current 0A is 1.65V on FRDM powerstage (voltage measured range 0-3.3V) -> shift to left */

    /* Read and store command 2 result from ADC channel A */
    ui32ADCRes = ADC0->RESFIFO[0];
    ui16Data = (uint16_t)(ui32ADCRes & ADC_RESFIFO_D_MASK);
    ui16IB = ui16Data << 1U;

    /* Read and store command 3 result from ADC channel A */
    ui32ADCRes = ADC0->RESFIFO[0];
    ui16Data = (uint16_t)(ui32ADCRes & ADC_RESFIFO_D_MASK);
    ui16UBus = ui16Data;

    /* Read and store command 1 result from ADC channel B */
    ui32ADCRes = ADC0->RESFIFO[1];
    ui16Data = (uint16_t)(ui32ADCRes & ADC_RESFIFO_D_MASK);
    ui16IC = ui16Data << 1U;

    f16UDcBus = (frac16_t)ui16UBus;

    /* Update PWM register values */
    UpdatePWM(f16DutyA, f16DutyB, f16DutyC, PWM0);

    /* Add empty instructions for correct interrupt flag clearing */
    M1_END_OF_ISR;
}

/*!
 * @brief   Update PWM register values
 *
 * @param    in    frac16_t f16PhA - Duty cycle phase A
 *                 frac16_t f16PhB - Duty cycle phase B
 *                 frac16_t f16PhC - Duty cycle phase C
 * @param    ptr   PWM_Type *pPWMBase - pointer to PWM base
 *
 * @return  none
 */
static void UpdatePWM(frac16_t f16PhA, frac16_t f16PhB, frac16_t f16PhC, PWM_Type *pPWMBase)
{
    /* PWM duty cycles calculation */
    uint16_t ui16Modulo;
    frac16_t f16DutyCycle;

    /* Modulo read from PWM val1 register */
    ui16Modulo = pPWMBase->SM[0].VAL1 + 1;

   /* Phase A - duty cycle calculation */
    f16DutyCycle = MLIB_Mul_F16(ui16Modulo, f16PhA);
    pPWMBase->SM[0].VAL2 = (uint16_t)MLIB_Neg_F16(f16DutyCycle);
    pPWMBase->SM[0].VAL3 = (uint16_t)f16DutyCycle;

    /* Phase B - duty cycle calculation */
    f16DutyCycle = MLIB_Mul_F16(ui16Modulo, f16PhB);
    pPWMBase->SM[1].VAL2 = (uint16_t)MLIB_Neg_F16(f16DutyCycle);
    pPWMBase->SM[1].VAL3 = (uint16_t)f16DutyCycle;

    /* Phase C - duty cycle calculation */
    f16DutyCycle = MLIB_Mul_F16(ui16Modulo, f16PhC);
    pPWMBase->SM[2].VAL2 = (uint16_t)MLIB_Neg_F16(f16DutyCycle);
    pPWMBase->SM[2].VAL3 = (uint16_t)f16DutyCycle;

    /* Set LDOK bit for all sub0, sub1, sub2 and sub3 */
    pPWMBase->MCTRL |= PWM_MCTRL_LDOK(15);
}

/*!
 * @brief   Over current fault detection
 *
 * @param    ptr   PWM_Type *pPWMBase - pointer to PWM base
 *
 * @return  bool   Over current fault status
 */
static bool_t OverCurrentFault(PWM_Type *pPWMBase)
{
    bool_t bOCFaultRet;

    /* read over-current flags */
    bOCFaultRet = (((pPWMBase->FSTS & PWM_FSTS_FFPIN_MASK) >> 8) & (1 << 0U));

    /* clear faults flag */
    pPWMBase->FSTS = ((pPWMBase->FSTS & ~(uint16_t)(PWM_FSTS_FFLAG_MASK)) | (1 << 0U));

    return bOCFaultRet;
}

/*!
 * @brief   USART Module initialization
 *
 * @param   void
 *
 * @return  none
 */
static void InitUSART0(void)
{
    usart_config_t config;

    /* Attach main clock divide to FLEXCOMM0 */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM0);

    /*
     *   usartConfig->baudRate_Bps = 115200U;
     *   usartConfig->parityMode = kUSART_ParityDisabled;
     *   usartConfig->stopBitCount = kUSART_OneStopBit;
     *   usartConfig->bitCountPerChar = kUSART_8BitsPerChar;
     *   usartConfig->loopback = false;
     *   usartConfig->enableTx = false;
     *   usartConfig->enableRx = false;
    */
    USART_GetDefaultConfig(&config);
    /* Override the Default configuration to satisfy FreeMASTER needs */
    config.baudRate_Bps = 115200U;
    config.enableTx = true;
    config.enableRx = true;

    /* Clock for USART0 peripheral is 12 MHz */
    USART_Init((USART_Type*)USART0, &config, 12000000U);

    /* Register communication module used by FreeMASTER driver. */
    FMSTR_SerialSetBaseAddress((USART_Type*)USART0);

#if FMSTR_SHORT_INTR || FMSTR_LONG_INTR
    /* Enable UART interrupts. */
    EnableIRQ(BOARD_UART_IRQ);
    EnableGlobalIRQ(0);
#endif
}

/*!
 * @brief   FreeMASTER middleware initialization
 *
 * @param   void
 *
 * @return  none
 */
static void InitFreeMASTER(void)
{
  /* FreeMASTER middleware initialization */
  FMSTR_Init();
  /* FreeMASTER recorder 0 configuration initialization  */
  FMSTR_RecorderCreate(0, &FreeMASTER_Recorder_0);
}
