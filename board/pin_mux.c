/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v14.0
processor: LPC5536
package_id: LPC5536JBD64
mcu_data: ksdk2_0
processor_version: 14.0.2
pin_labels:
- {pin_num: '62', pin_signal: PIO1_11/FC1_TXD_SCL_MISO_WS/CT_INP5/HS_SPI_SSEL0/FC6_SCK/PWM0_A0/EXTTRIG_IN8, label: LED_BLUE, identifier: LED_BLUE}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm33_core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '43', peripheral: CAN0, signal: CAN_RD, pin_signal: PIO1_3/CAN0_RD/FC2_TXD_SCL_MISO_WS/SCT0_OUT4/PDM_DATA1/HS_SPI_MISO/PWM0_A3}
  - {pin_num: '42', peripheral: CAN0, signal: CAN_TD, pin_signal: PIO1_2/CAN0_TD/CTIMER0_MAT3/SCT_GPI6/PDM_CLK1/HS_SPI_SCK/PWM0_B0/AOI0_OUT0}
  - {pin_num: '62', peripheral: PWM0, signal: 'A, 0', pin_signal: PIO1_11/FC1_TXD_SCL_MISO_WS/CT_INP5/HS_SPI_SSEL0/FC6_SCK/PWM0_A0/EXTTRIG_IN8}
  - {pin_num: '45', peripheral: PWM0, signal: 'A, 1', pin_signal: PIO0_24/FC0_RXD_SDA_MOSI_DATA/CT_INP8/SCT_GPI0/I3C0_SDA/TRACEDATA0/SECURE_GPIO0_24/PWM0_A1/PWM0_X0/HSCMP0_IN0}
  - {pin_num: '59', peripheral: PWM0, signal: 'B, 0', pin_signal: PIO0_6/FC3_SCK/CT_INP13/CTIMER4_MAT0/SCT_GPI6/FLEXSPI0_DATA0/SCT0_OUT6/FC7_RXD_SDA_MOSI_DATA/SECURE_GPIO0_6/PWM0_B0/EXTTRIG_IN1}
  - {pin_num: '41', peripheral: PWM0, signal: 'B, 1', pin_signal: PIO0_26/TAMPER2/FC2_RXD_SDA_MOSI_DATA/CLKOUT/CT_INP14/SCT0_OUT5/PDM_CLK0/FC0_SCK/HS_SPI_MOSI/SECURE_GPIO0_26/PWM0_B1}
  - {pin_num: '18', peripheral: OPAMP0, signal: 'DM, 0', pin_signal: OPAMP0_INN}
  - {pin_num: '17', peripheral: OPAMP0, signal: 'DP, 0', pin_signal: PIO0_8/FC3_SSEL3/FC5_RXD_SDA_MOSI_DATA/SWO/PDM_DATA1/SECURE_GPIO0_8/OPAMP0_INP}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M33 */
void BOARD_InitPins(void)
{
    /* Enables the clock for the I/O controller.: Enable Clock. */
    CLOCK_EnableClock(kCLOCK_Iocon);


    IOCON->PIO[0][24] = ((IOCON->PIO[0][24] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT024 (pin 45) is configured as PWM0_A1. */
                         | IOCON_PIO_FUNC(0x0Bu)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO0_24_DIGIMODE_DIGITAL));


    IOCON->PIO[0][26] = ((IOCON->PIO[0][26] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT026 (pin 41) is configured as PWM0_B1. */
                         | IOCON_PIO_FUNC(0x0Bu)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO0_26_DIGIMODE_DIGITAL));


    IOCON->PIO[0][6] = ((IOCON->PIO[0][6] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Signal(function) select: PORT06 (pin 59) is configured as PWM0_B0. */
                        | IOCON_PIO_FUNC(0x0Bu)

                        /* Select Digital mode: Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO0_6_DIGIMODE_DIGITAL));


    IOCON->PIO[0][8] = ((IOCON->PIO[0][8] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Signal(function) select: PORT08 (pin 17) is configured as OPAMP0_INP. */
                        | IOCON_PIO_FUNC(0x00u)

                        /* Select Digital mode: Disable digital mode.
                         * Digital input set to 0. */
                        | IOCON_PIO_DIGIMODE(PIO0_8_DIGIMODE_ANALOG));


    IOCON->PIO[1][11] = ((IOCON->PIO[1][11] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Signal(function) select: PORT111 (pin 62) is configured as PWM0_A0. */
                         | IOCON_PIO_FUNC(0x0Bu)

                         /* Select Digital mode: Enable Digital mode.
                          * Digital input is enabled. */
                         | IOCON_PIO_DIGIMODE(PIO1_11_DIGIMODE_DIGITAL));


    IOCON->PIO[1][2] = ((IOCON->PIO[1][2] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Signal(function) select: PORT12 (pin 42) is configured as CAN0_TD. */
                        | IOCON_PIO_FUNC(0x01u)

                        /* Select Digital mode: Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_2_DIGIMODE_DIGITAL));


    IOCON->PIO[1][3] = ((IOCON->PIO[1][3] &
                         /* Mask bits to zero which are setting */
                         (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                        /* Signal(function) select: PORT13 (pin 43) is configured as CAN0_RD. */
                        | IOCON_PIO_FUNC(0x01u)

                        /* Select Digital mode: Enable Digital mode.
                         * Digital input is enabled. */
                        | IOCON_PIO_DIGIMODE(PIO1_3_DIGIMODE_DIGITAL));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
