/*
 * Copyright (c) 2022 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This file is derivative of CMSIS V5.9.0 startup_ARMCM33.c
 * Git SHA: 2b7495b8535bdcb306dac29b9ded4cfb679d7e5c
 */

/* NS linker scripts using the default CMSIS style naming conventions, while the
 * secure and bl2 linker scripts remain untouched (region.h compatibility).
 * To be compatible with the untouched files (which using ARMCLANG naming style),
 * we have to override __INITIAL_SP and __STACK_LIMIT labels. */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) 
#include "cmsis_override.h"
#endif

#include "cmsis.h"

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
extern uint64_t __STACK_SEAL;
#endif

typedef void(*VECTOR_TABLE_Type)(void);

extern void __PROGRAM_START(void) __NO_RETURN;

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
void Reset_Handler  (void) __NO_RETURN;

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
#define DEFAULT_IRQ_HANDLER(handler_name)  \
void __WEAK handler_name(void) __NO_RETURN; \
void handler_name(void) { \
    while(1); \
}

/* Exceptions */
DEFAULT_IRQ_HANDLER(NMI_Handler)
DEFAULT_IRQ_HANDLER(HardFault_Handler)
DEFAULT_IRQ_HANDLER(MemManage_Handler)
DEFAULT_IRQ_HANDLER(BusFault_Handler)
DEFAULT_IRQ_HANDLER(UsageFault_Handler)
DEFAULT_IRQ_HANDLER(SecureFault_Handler)
DEFAULT_IRQ_HANDLER(SVC_Handler)
DEFAULT_IRQ_HANDLER(DebugMon_Handler)
DEFAULT_IRQ_HANDLER(PendSV_Handler)
DEFAULT_IRQ_HANDLER(SysTick_Handler)

DEFAULT_IRQ_HANDLER(WDT_BOD_IRQHandler)
DEFAULT_IRQ_HANDLER(DMA0_IRQHandler)
DEFAULT_IRQ_HANDLER(GINT0_IRQHandler)
DEFAULT_IRQ_HANDLER(GINT1_IRQHandler)
DEFAULT_IRQ_HANDLER(PIN_INT0_IRQHandler)
DEFAULT_IRQ_HANDLER(PIN_INT1_IRQHandler)
DEFAULT_IRQ_HANDLER(PIN_INT2_IRQHandler)
DEFAULT_IRQ_HANDLER(PIN_INT3_IRQHandler)
DEFAULT_IRQ_HANDLER(UTICK0_IRQHandler)
DEFAULT_IRQ_HANDLER(MRT0_IRQHandler)
DEFAULT_IRQ_HANDLER(CTIMER0_IRQHandler)
DEFAULT_IRQ_HANDLER(CTIMER1_IRQHandler)
DEFAULT_IRQ_HANDLER(SCT0_IRQHandler)
DEFAULT_IRQ_HANDLER(CTIMER3_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM0_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM1_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM2_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM3_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM4_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM5_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM6_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM7_IRQHandler)
DEFAULT_IRQ_HANDLER(ADC0_IRQHandler)
DEFAULT_IRQ_HANDLER(ADC1_IRQHandler)
DEFAULT_IRQ_HANDLER(ACMP_IRQHandler)
DEFAULT_IRQ_HANDLER(DMIC_IRQHandler)
DEFAULT_IRQ_HANDLER(HWVAD0_IRQHandler)
DEFAULT_IRQ_HANDLER(USB0_NEEDCLK_IRQHandler)
DEFAULT_IRQ_HANDLER(USB0_IRQHandler)
DEFAULT_IRQ_HANDLER(RTC_IRQHandler)
DEFAULT_IRQ_HANDLER(EZH_ARCH_B0_IRQHandler)
DEFAULT_IRQ_HANDLER(WAKEUP_IRQHandler)
DEFAULT_IRQ_HANDLER(PIN_INT4_IRQHandler)
DEFAULT_IRQ_HANDLER(PIN_INT5_IRQHandler)
DEFAULT_IRQ_HANDLER(PIN_INT6_IRQHandler)
DEFAULT_IRQ_HANDLER(PIN_INT7_IRQHandler)
DEFAULT_IRQ_HANDLER(CTIMER2_IRQHandler)
DEFAULT_IRQ_HANDLER(CTIMER4_IRQHandler)
DEFAULT_IRQ_HANDLER(OS_EVENT_IRQHandler)
DEFAULT_IRQ_HANDLER(FlexSPI0_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved56_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved57_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved58_IRQHandler)
DEFAULT_IRQ_HANDLER(CAN0_IRQ0_IRQHandler)
DEFAULT_IRQ_HANDLER(CAN0_IRQ1_IRQHandler)
DEFAULT_IRQ_HANDLER(SPI_FILTER_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved62_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved63_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved64_IRQHandler)
DEFAULT_IRQ_HANDLER(SEC_HYPERVISOR_CALL_IRQHandler)
DEFAULT_IRQ_HANDLER(SEC_GPIO_INT0_IRQ0_IRQHandler)
DEFAULT_IRQ_HANDLER(SEC_GPIO_INT0_IRQ1_IRQHandler)
DEFAULT_IRQ_HANDLER(Freqme_IRQHandler)
DEFAULT_IRQ_HANDLER(SEC_VIO_IRQHandler)
DEFAULT_IRQ_HANDLER(SHA_IRQHandler)
DEFAULT_IRQ_HANDLER(PKC_IRQHandler)
DEFAULT_IRQ_HANDLER(PUF_IRQHandler)
DEFAULT_IRQ_HANDLER(POWERQUAD_IRQHandler)
DEFAULT_IRQ_HANDLER(DMA1_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXCOMM8_IRQHandler)
DEFAULT_IRQ_HANDLER(CDOG_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved77_IRQHandler)
DEFAULT_IRQ_HANDLER(I3C0_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved79_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved80_IRQHandler)
DEFAULT_IRQ_HANDLER(CSS_IRQ1_IRQHandler)
DEFAULT_IRQ_HANDLER(Tamper_IRQHandler)
DEFAULT_IRQ_HANDLER(Analog_Glitch_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved84_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved85_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved86_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved87_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved88_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved89_IRQHandler)
DEFAULT_IRQ_HANDLER(DAC0_IRQHandler)
DEFAULT_IRQ_HANDLER(DAC1_IRQHandler)
DEFAULT_IRQ_HANDLER(DAC2_IRQHandler)
DEFAULT_IRQ_HANDLER(HSCMP0_IRQHandler)
DEFAULT_IRQ_HANDLER(HSCMP1_IRQHandler)
DEFAULT_IRQ_HANDLER(HSCMP2_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_CAPTURE_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_FAULT_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_RELOAD_ERROR_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_COMPARE0_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_RELOAD0_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_COMPARE1_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_RELOAD1_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_COMPARE2_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_RELOAD2_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_COMPARE3_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM0_RELOAD3_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_CAPTURE_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_FAULT_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_RELOAD_ERROR_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_COMPARE0_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_RELOAD0_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_COMPARE1_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_RELOAD1_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_COMPARE2_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_RELOAD2_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_COMPARE3_IRQHandler)
DEFAULT_IRQ_HANDLER(FLEXPWM1_RELOAD3_IRQHandler)
DEFAULT_IRQ_HANDLER(ENC0_COMPARE_IRQHandler)
DEFAULT_IRQ_HANDLER(ENC0_HOME_IRQHandler)
DEFAULT_IRQ_HANDLER(ENC0_WDG_IRQHandler)
DEFAULT_IRQ_HANDLER(ENC0_IDX_IRQHandler)
DEFAULT_IRQ_HANDLER(ENC1_COMPARE_IRQHandler)
DEFAULT_IRQ_HANDLER(ENC1_HOME_IRQHandler)
DEFAULT_IRQ_HANDLER(ENC1_WDG_IRQHandler)
DEFAULT_IRQ_HANDLER(ENC1_IDX_IRQHandler)
DEFAULT_IRQ_HANDLER(ITRC0_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved127_IRQHandler)
DEFAULT_IRQ_HANDLER(CSSV2_ERR_IRQHandler)
DEFAULT_IRQ_HANDLER(PKC_ERR_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved130_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved131_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved132_IRQHandler)
DEFAULT_IRQ_HANDLER(Reserved133_IRQHandler)
DEFAULT_IRQ_HANDLER(FLASH_IRQHandler)
DEFAULT_IRQ_HANDLER(RAM_PARITY_ECC_ERR_IRQHandler)

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const VECTOR_TABLE_Type __VECTOR_TABLE[];
       const VECTOR_TABLE_Type __VECTOR_TABLE[] __VECTOR_TABLE_ATTRIBUTE = {
  (VECTOR_TABLE_Type)(&__INITIAL_SP),            /*      Initial Stack Pointer */
  Reset_Handler,                     /* Reset Handler */
  NMI_Handler,                       /* NMI Handler*/
  HardFault_Handler,                 /* Hard Fault Handler*/
  MemManage_Handler,                 /* MPU Fault Handler*/
  BusFault_Handler,                  /* Bus Fault Handler*/
  UsageFault_Handler,                /* Usage Fault Handler*/
  SecureFault_Handler,               /* Secure Fault Handler */
  0,                                 /* Reserved*/
  0,                                 /* Reserved*/
  0,                                 /* Reserved*/
  SVC_Handler,                       /* SVCall Handler*/
  DebugMon_Handler,                  /* Debug Monitor Handler*/
  0,                                 /* Reserved*/
  PendSV_Handler,                    /* PendSV Handler*/
  SysTick_Handler,                   /* SysTick Handler*/

/* External Interrupts*/
  WDT_BOD_IRQHandler,                /* Windowed watchdog timer, Brownout detect, Flash interrupt */
  DMA0_IRQHandler,                   /* DMA0 controller */
  GINT0_IRQHandler,                  /* GPIO group 0 */
  GINT1_IRQHandler,                  /* GPIO group 1 */
  PIN_INT0_IRQHandler,               /* Pin interrupt 0 or pattern match engine slice 0 */
  PIN_INT1_IRQHandler,               /* Pin interrupt 1or pattern match engine slice 1 */
  PIN_INT2_IRQHandler,               /* Pin interrupt 2 or pattern match engine slice 2 */
  PIN_INT3_IRQHandler,               /* Pin interrupt 3 or pattern match engine slice 3 */
  UTICK0_IRQHandler,                 /* Micro-tick Timer */
  MRT0_IRQHandler,                   /* Multi-rate timer */
  CTIMER0_IRQHandler,                /* Standard counter/timer CTIMER0 */
  CTIMER1_IRQHandler,                /* Standard counter/timer CTIMER1 */
  SCT0_IRQHandler,                   /* SCTimer/PWM */
  CTIMER3_IRQHandler,                /* Standard counter/timer CTIMER3 */
  FLEXCOMM0_IRQHandler,              /* Flexcomm Interface 0 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM1_IRQHandler,              /* Flexcomm Interface 1 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM2_IRQHandler,              /* Flexcomm Interface 2 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM3_IRQHandler,              /* Flexcomm Interface 3 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM4_IRQHandler,              /* Flexcomm Interface 4 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM5_IRQHandler,              /* Flexcomm Interface 5 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM6_IRQHandler,              /* Flexcomm Interface 6 (USART, SPI, I2C, I2S, FLEXCOMM) */
  FLEXCOMM7_IRQHandler,              /* Flexcomm Interface 7 (USART, SPI, I2C, I2S, FLEXCOMM) */
  ADC0_IRQHandler,                   /* ADC0  */
  ADC1_IRQHandler,                   /* ADC1 */
  ACMP_IRQHandler,                   /* ACMP  interrupts */
  DMIC_IRQHandler,                   /* Digital microphone and DMIC subsystem */
  HWVAD0_IRQHandler,                 /* Hardware Voice Activity Detector */
  USB0_NEEDCLK_IRQHandler,           /* USB Activity Wake-up Interrupt */
  USB0_IRQHandler,                   /* USB device */
  RTC_IRQHandler,                    /* RTC alarm and wake-up interrupts */
  EZH_ARCH_B0_IRQHandler,            /* EZH interrupt */
  WAKEUP_IRQHandler,                 /* Wakeup interrupt */
  PIN_INT4_IRQHandler,               /* Pin interrupt 4 or pattern match engine slice 4 int */
  PIN_INT5_IRQHandler,               /* Pin interrupt 5 or pattern match engine slice 5 int */
  PIN_INT6_IRQHandler,               /* Pin interrupt 6 or pattern match engine slice 6 int */
  PIN_INT7_IRQHandler,               /* Pin interrupt 7 or pattern match engine slice 7 int */
  CTIMER2_IRQHandler,                /* Standard counter/timer CTIMER2 */
  CTIMER4_IRQHandler,                /* Standard counter/timer CTIMER4 */
  OS_EVENT_IRQHandler,               /* OSEVTIMER0 and OSEVTIMER0_WAKEUP interrupts */
  FlexSPI0_IRQHandler,               /* FlexSPI interrupt */
  Reserved56_IRQHandler,             /* Reserved interrupt */
  Reserved57_IRQHandler,             /* Reserved interrupt */
  Reserved58_IRQHandler,             /* Reserved interrupt */
  CAN0_IRQ0_IRQHandler,              /* CAN0 interrupt0 */
  CAN0_IRQ1_IRQHandler,              /* CAN0 interrupt1 */
  SPI_FILTER_IRQHandler,             /* SPI Filter interrupt */
  Reserved62_IRQHandler,             /* Reserved interrupt */
  Reserved63_IRQHandler,             /* Reserved interrupt */
  Reserved64_IRQHandler,             /* Reserved interrupt */
  SEC_HYPERVISOR_CALL_IRQHandler,    /* SEC_HYPERVISOR_CALL interrupt */
  SEC_GPIO_INT0_IRQ0_IRQHandler,     /* SEC_GPIO_INT0_IRQ0 interrupt */
  SEC_GPIO_INT0_IRQ1_IRQHandler,     /* SEC_GPIO_INT0_IRQ1 interrupt */
  Freqme_IRQHandler,                 /* frequency measure interrupt */
  SEC_VIO_IRQHandler,                /* SEC_VIO interrupt */
  SHA_IRQHandler,                    /* SHA interrupt */
  PKC_IRQHandler,                    /* PKC interrupt */
  PUF_IRQHandler,                    /* PUF interrupt */
  POWERQUAD_IRQHandler,              /* PowerQuad interrupt */
  DMA1_IRQHandler,                   /* DMA1 interrupt */
  FLEXCOMM8_IRQHandler,              /* Flexcomm Interface 8 (SPI, , FLEXCOMM) */
  CDOG_IRQHandler,                   /* CDOG interrupt */
  Reserved77_IRQHandler,             /* Reserved interrupt */
  I3C0_IRQHandler,                   /* I3C interrupt */
  Reserved79_IRQHandler,             /* Reserved interrupt */
  Reserved80_IRQHandler,             /* Reserved interrupt */
  CSS_IRQ1_IRQHandler,               /* CSS_IRQ1 */
  Tamper_IRQHandler,                 /* Tamper */
  Analog_Glitch_IRQHandler,          /* Analog_Glitch */
  Reserved84_IRQHandler,             /* Reserved interrupt */
  Reserved85_IRQHandler,             /* Reserved interrupt */
  Reserved86_IRQHandler,             /* Reserved interrupt */
  Reserved87_IRQHandler,             /* Reserved interrupt */
  Reserved88_IRQHandler,             /* Reserved interrupt */
  Reserved89_IRQHandler,             /* Reserved interrupt */
  DAC0_IRQHandler,                   /* dac0 interrupt */
  DAC1_IRQHandler,                   /* dac1 interrupt */
  DAC2_IRQHandler,                   /* dac2 interrupt */
  HSCMP0_IRQHandler,                 /* hscmp0 interrupt */
  HSCMP1_IRQHandler,                 /* hscmp1 interrupt */
  HSCMP2_IRQHandler,                 /* hscmp2 interrupt */
  FLEXPWM0_CAPTURE_IRQHandler,       /* flexpwm0_capture interrupt */
  FLEXPWM0_FAULT_IRQHandler,         /* flexpwm0_fault interrupt */
  FLEXPWM0_RELOAD_ERROR_IRQHandler,  /* flexpwm0_reload_error interrupt */
  FLEXPWM0_COMPARE0_IRQHandler,      /* flexpwm0_compare0 interrupt */
  FLEXPWM0_RELOAD0_IRQHandler,       /* flexpwm0_reload0 interrupt */
  FLEXPWM0_COMPARE1_IRQHandler,      /* flexpwm0_compare1 interrupt */
  FLEXPWM0_RELOAD1_IRQHandler,       /* flexpwm0_reload1 interrupt */
  FLEXPWM0_COMPARE2_IRQHandler,      /* flexpwm0_compare2 interrupt */
  FLEXPWM0_RELOAD2_IRQHandler,       /* flexpwm0_reload2 interrupt */
  FLEXPWM0_COMPARE3_IRQHandler,      /* flexpwm0_compare3 interrupt */
  FLEXPWM0_RELOAD3_IRQHandler,       /* flexpwm0_reload3 interrupt */
  FLEXPWM1_CAPTURE_IRQHandler,       /* flexpwm1_capture interrupt */
  FLEXPWM1_FAULT_IRQHandler,         /* flexpwm1_fault interrupt */
  FLEXPWM1_RELOAD_ERROR_IRQHandler,  /* flexpwm1_reload_error interrupt */
  FLEXPWM1_COMPARE0_IRQHandler,      /* flexpwm1_compare0 interrupt */
  FLEXPWM1_RELOAD0_IRQHandler,       /* flexpwm1_reload0 interrupt */
  FLEXPWM1_COMPARE1_IRQHandler,      /* flexpwm1_compare1 interrupt */
  FLEXPWM1_RELOAD1_IRQHandler,       /* flexpwm1_reload1 interrupt */
  FLEXPWM1_COMPARE2_IRQHandler,      /* flexpwm1_compare2 interrupt */
  FLEXPWM1_RELOAD2_IRQHandler,       /* flexpwm1_reload2 interrupt */
  FLEXPWM1_COMPARE3_IRQHandler,      /* flexpwm1_compare3 interrupt */
  FLEXPWM1_RELOAD3_IRQHandler,       /* flexpwm1_reload3 interrupt */
  ENC0_COMPARE_IRQHandler,           /* enc0_compare interrupt */
  ENC0_HOME_IRQHandler,              /* enc0_home interrupt */
  ENC0_WDG_IRQHandler,               /* enc0_wdg interrupt */
  ENC0_IDX_IRQHandler,               /* enc0_idx interrupt */
  ENC1_COMPARE_IRQHandler,           /* enc1_compare interrupt */
  ENC1_HOME_IRQHandler,              /* enc1_home interrupt */
  ENC1_WDG_IRQHandler,               /* enc1_wdg interrupt */
  ENC1_IDX_IRQHandler,               /* enc1_idx interrupt */
  ITRC0_IRQHandler,                  /* itrc0 interrupt */
  Reserved127_IRQHandler,            /* Reserved interrupt */
  CSSV2_ERR_IRQHandler,              /* cssv2_err interrupt */
  PKC_ERR_IRQHandler,                /* pkc_err interrupt */
  Reserved130_IRQHandler,            /* Reserved interrupt */
  Reserved131_IRQHandler,            /* Reserved interrupt */
  Reserved132_IRQHandler,            /* Reserved interrupt */
  Reserved133_IRQHandler,            /* Reserved interrupt */
  FLASH_IRQHandler,                  /* flash interrupt */
  RAM_PARITY_ECC_ERR_IRQHandler,     /* ram_parity_ecc_err interrupt */
};

#if defined(__ICCARM__)
extern typeof(__vector_table) __attribute__ ((alias ("__vector_table"))) __Vectors;
#endif

#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
void Reset_Handler(void)
{
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    __disable_irq();
#endif
    __set_PSP((uint32_t)(&__INITIAL_SP));

    __set_MSPLIM((uint32_t)(&__STACK_LIMIT));
    __set_PSPLIM((uint32_t)(&__STACK_LIMIT));

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
    __TZ_set_STACKSEAL_S((uint32_t *)(&__STACK_SEAL));
#endif

    SystemInit();                             /* CMSIS System Initialization */
    __PROGRAM_START();                        /* Enter PreMain (C library entry point) */
}
