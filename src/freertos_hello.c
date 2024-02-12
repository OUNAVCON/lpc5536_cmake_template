/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include <stdint.h>

/* Freescale includes. */
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Task priorities. */
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void hello_task(void *pvParameters);


// #define VERSION_MAJOR 0x0a
// #define VERSION_MINOR 0x0b
// #define VERSION_BUILD 0x0c

// uint32_t __attribute__((section (".BLHeader"))) blHeader[] = {0xFEEDA5A5, 
//                                                               0x00000000, 
//                                                               0x00000000, 
//                                                               0xCCCCCCCC, 
//                                                               0xDDDDDDDD,
//                                                               (uint32_t)( ((VERSION_MAJOR & 0xFF) << 16) | ((VERSION_MINOR & 0xFF) << 8) | ((VERSION_BUILD & 0xFF)) )};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Application entry point.
 */
int main(void)
{
    /* Init board hardware. */
    /* attach main clock divide to FLEXCOMM0 (debug console) */
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom0Clk, 0u, false);
    CLOCK_SetClkDiv(kCLOCK_DivFlexcom0Clk, 1u, true);
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    //BOARD_InitDebugConsole();
    if (xTaskCreate(hello_task, "Hello_task", configMINIMAL_STACK_SIZE + 100, NULL, hello_task_PRIORITY, NULL) !=
        pdPASS)
    {
        PRINTF("Task creation failed!.\r\n");
        while (1)
            ;
    }
    vTaskStartScheduler();
    for (;;)
        ;
}

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void hello_task(void *pvParameters)
{


    for (;;)
    {
        PRINTF("Hello world.\r\n");
         GPIO_PortToggle(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PORT, \
                    1U << BOARD_LED_BLUE_GPIO_PIN);
        vTaskDelay(100);
        //vTaskSuspend(NULL);
    }
}
