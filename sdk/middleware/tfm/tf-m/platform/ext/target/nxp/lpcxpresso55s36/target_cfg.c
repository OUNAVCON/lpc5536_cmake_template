/*
 * Copyright (c) 2018-2022 Arm Limited. All rights reserved.
 * Copyright (c) 2019-2022 NXP. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "target_cfg.h"
#include "Driver_Common.h"
#include "platform_description.h"
#include "device_definition.h"
#include "region_defs.h"
#include "tfm_plat_defs.h"
#include "region.h"
#include "utilities.h"
#include "tfm_spm_log.h"

/* The section names come from the scatter file */
REGION_DECLARE(Load$$LR$$, LR_NS_PARTITION, $$Base);
REGION_DECLARE(Image$$, ER_VENEER, $$Base);
REGION_DECLARE(Image$$, VENEER_ALIGN, $$Limit);

const struct memory_region_limits memory_regions = {
    .non_secure_code_start =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base),

    .non_secure_partition_base =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base),

    .non_secure_partition_limit =
        (uint32_t)&REGION_NAME(Load$$LR$$, LR_NS_PARTITION, $$Base) +
        NS_PARTITION_SIZE - 1,

    .veneer_base =
        (uint32_t)&REGION_NAME(Image$$, ER_VENEER, $$Base),

    .veneer_limit =
        (uint32_t)&REGION_NAME(Image$$, VENEER_ALIGN, $$Limit),
};

/* Allows software, via SAU, to define the code region as a NSC */
#define NSCCFG_CODENSC  1

/* Define Peripherals NS address range for the platform */
#define PERIPHERALS_BASE_NS_START (0x40000000)
#define PERIPHERALS_BASE_NS_END   (0x4FFFFFFF)

/* Enable system reset request for CPU 0 */
#define ENABLE_CPU0_SYSTEM_RESET_REQUEST (1U << 4U)

/* To write into AIRCR register, 0x5FA value must be write to the VECTKEY field,
 * otherwise the processor ignores the write.
 */
#define SCB_AIRCR_WRITE_MASK ((0x5FAUL << SCB_AIRCR_VECTKEY_Pos))

struct platform_data_t tfm_peripheral_std_uart = {
        USART0_BASE_NS,
        USART0_BASE_NS + 0xFFF,
        0,
        0
};

struct platform_data_t tfm_peripheral_timer0 = {
        CTIMER2_BASE,
        CTIMER2_BASE + 0xFFF,
        &(AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP1_MEM_RULE1),
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE1_CTIMER2_SHIFT
};

enum tfm_plat_err_t enable_fault_handlers(void)
{
    /* Explicitly set secure fault priority to the highest */
    NVIC_SetPriority(SecureFault_IRQn, 0);

    /* Enables BUS, MEM, USG and Secure faults */
    SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk
                  | SCB_SHCSR_BUSFAULTENA_Msk
                  | SCB_SHCSR_MEMFAULTENA_Msk
                  | SCB_SHCSR_SECUREFAULTENA_Msk;
    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t system_reset_cfg(void)
{
    uint32_t reg_value = SCB->AIRCR;

    /* Clear SCB_AIRCR_VECTKEY value */
    reg_value &= ~(uint32_t)(SCB_AIRCR_VECTKEY_Msk);

    /* Enable system reset request only to the secure world */
    reg_value |= (uint32_t)(SCB_AIRCR_WRITE_MASK | SCB_AIRCR_SYSRESETREQS_Msk);

    SCB->AIRCR = reg_value;

    return TFM_PLAT_ERR_SUCCESS;
}

enum tfm_plat_err_t init_debug(void)
{

#if !defined(DAUTH_CHIP_DEFAULT)
#error "Debug features are set during provisioning. Application is not able to change them as the SYSCTRL->DEBUG_LOCK_EN is locked by the MCU secure boot.  "
#endif
    return TFM_PLAT_ERR_SUCCESS;
}

/*----------------- NVIC interrupt target state to NS configuration ----------*/
enum tfm_plat_err_t nvic_interrupt_target_state_cfg(void)
{
    /* Target every interrupt to NS; unimplemented interrupts will be WI */
    for (uint8_t i=0; i<sizeof(NVIC->ITNS)/sizeof(NVIC->ITNS[0]); i++) {
        NVIC->ITNS[i] = 0xFFFFFFFF;
    }

    /* Make sure that MPC and PPC are targeted to S state */
    NVIC_ClearTargetState(SEC_VIO_IRQn);

    return TFM_PLAT_ERR_SUCCESS;
}

/*----------------- NVIC interrupt enabling for S peripherals ----------------*/
enum tfm_plat_err_t nvic_interrupt_enable(void)
{

    /* MPC/PPC interrupt enabling */

    NVIC_EnableIRQ(SEC_VIO_IRQn);

    return TFM_PLAT_ERR_SUCCESS;
}

/*------------------- SAU/IDAU configuration functions -----------------------*/

void sau_and_idau_cfg(void)
{
    uint32_t region = 0U;

    /* Ensure all memory accesses are completed */
    __DMB();

    /* Enables SAU */
    TZ_SAU_Enable();

    /* Configures SAU regions to be non-secure */
    SAU->RNR  = region++;
    SAU->RBAR = (memory_regions.non_secure_partition_base
                & SAU_RBAR_BADDR_Msk);
    SAU->RLAR = (memory_regions.non_secure_partition_limit
                & SAU_RLAR_LADDR_Msk)
                | SAU_RLAR_ENABLE_Msk;

    SAU->RNR  = region++;
    SAU->RBAR = (NS_DATA_START & SAU_RBAR_BADDR_Msk);
    SAU->RLAR = (NS_DATA_LIMIT & SAU_RLAR_LADDR_Msk) | SAU_RLAR_ENABLE_Msk;

    /* Configures veneers region to be non-secure callable */
    SAU->RNR  = region++;
    SAU->RBAR = (memory_regions.veneer_base  & SAU_RBAR_BADDR_Msk);
    SAU->RLAR = (memory_regions.veneer_limit & SAU_RLAR_LADDR_Msk)
                | SAU_RLAR_ENABLE_Msk
                | SAU_RLAR_NSC_Msk;

    /* Configure the peripherals space */
    SAU->RNR  = region++;
    SAU->RBAR = (PERIPHERALS_BASE_NS_START & SAU_RBAR_BADDR_Msk);
    SAU->RLAR = (PERIPHERALS_BASE_NS_END & SAU_RLAR_LADDR_Msk)
                | SAU_RLAR_ENABLE_Msk;

    /* Ensure the write is completed and flush pipeline */
    __DSB();
    __ISB();

#if TARGET_DEBUG_LOG
    SPMLOG_DBGMSG("=== [SAU NS] =======\r\n");
    SPMLOG_DBGMSGVAL("NS ROM starts from : ",
                                      memory_regions.non_secure_partition_base);
    SPMLOG_DBGMSGVAL("NS ROM ends at : ",
                                      memory_regions.non_secure_partition_base +
                                     memory_regions.non_secure_partition_limit);
    SPMLOG_DBGMSGVAL("NS DATA start from : ", NS_DATA_START);
    SPMLOG_DBGMSGVAL("NS DATA ends at : ", NS_DATA_START + NS_DATA_LIMIT);
    SPMLOG_DBGMSGVAL("NSC starts with : ", memory_regions.veneer_base);
    SPMLOG_DBGMSGVAL("NSC ends at : ", memory_regions.veneer_base +
                                       memory_regions.veneer_limit);
    SPMLOG_DBGMSGVAL("PERIPHERALS starts with : ", PERIPHERALS_BASE_NS_START);
    SPMLOG_DBGMSGVAL("PERIPHERALS ends at : ", PERIPHERALS_BASE_NS_END);
#endif
}

/*------------------- Memory configuration functions -------------------------*/

int32_t mpc_init_cfg(void)
{
    uint32_t ns_region_id = 0;
    uint32_t ns_region_start_id = 0;
    uint32_t ns_region_end_id = 0;
    int i;

    /*
    * Starts changing actual configuration so issue DMB to ensure every
    * transaction has completed by now
    */
    __DMB();

    /* Configuration of AHB Secure Controller
     * Possible values for every memory sector or peripheral rule:
     *  0    Non-secure, user access allowed.
     *  1    Non-secure, privileged access allowed.
     *  2    Secure, user access allowed.
     *  3    Secure, privileged access allowed. */

    /* == On-Chip Flash region == */

    /* Flash region is divided into 8 sub-regions (sector). Each flash sub-regions (sector) is 32 kbytes. */
    /* 1) Set FLASH memory security access rule configuration to init value (0x3 = all regions set to secure and privileged user access) */
    AHB_SECURE_CTRL->FLASH_MEM_RULE = 0x33333333U;

#ifndef NS_QSPI_FLASH /* NS in On-chip Flash */

    /* The regions have to be alligned to 32 kB to cover the AHB Flash Region. */
    SPM_ASSERT((memory_regions.non_secure_partition_base % FLASH_SUBREGION_SIZE) == 0);
    SPM_ASSERT(((memory_regions.non_secure_partition_limit+1) % FLASH_SUBREGION_SIZE) == 0);

    /* 2) Set FLASH memory security access rule configuration (set to non-secure and non-privileged user access allowed).*/
    ns_region_start_id = memory_regions.non_secure_partition_base/FLASH_SUBREGION_SIZE;
    ns_region_end_id = (memory_regions.non_secure_partition_limit+1)/FLASH_SUBREGION_SIZE;

    /* Set to non-secure and non-privileged user access allowed */
    for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++)
    {
        /* Set regions the AHB controller for flash memory 0x0000_0000 - 0x0004_0000 */
        AHB_SECURE_CTRL->FLASH_MEM_RULE &= ~(0xF << (ns_region_id*4));
    }

#endif /* NS_QSPI_FLASH */

    /* == ROM region == */

    /* Each ROM sector is 4 kbytes. There are 32 ROM sectors in total. */
    /* Security control ROM memory configuration (0x3 = all regions set to secure and privileged user access). */
    for(i=0; i < 4; i++)
    {
        AHB_SECURE_CTRL->ROM_MEM_RULE[i] = 0x33333333U;
    }

    /* == RAMX region == */

    /* Each RAMX sub region is 4 kbytes.*/
    /* Security access rules for RAMX (0x3 = all regions set to secure and privileged user access). */
    AHB_SECURE_CTRL->RAMX_MEM_RULE0 = 0x00003333U; /* 0x0400_0000 - 0x0400_3FFF */

    /* == FlexSPI region == */

    /* FlexSPI0 0x0800 0000 to 0x0FFF FFFF 128 MB
            Region 0: 8 MB (32 * 256 KB)
            Region 1: 8 MB (4 * 2 MB)
            Region 2: 16 MB (4 * 4 MB)
            Region 3: 32 MB (4 * 8 MB)
            Region 4: 64 MB (4 * 16 MB) */

    /* 1) Set FLASH memory security access rule configuration to init value (0x3 = all regions set to secure and privileged user access) */
    for(i=0; i < 4; i++)
    {
        AHB_SECURE_CTRL->FLEXSPI0_REGION0_MEM_RULE[i] = 0x33333333U;
        AHB_SECURE_CTRL->FLEXSPI0_REGION1_4_MEM_RULE[i].FLEXSPI0_REGION_MEM_RULE0 = 0x00003333U;
    }

#ifdef NS_QSPI_FLASH /* NS in QSPI Flash */
    /* 2) Set FLASH memory security access rule configuration (set to non-secure and non-privileged user access allowed).*/

    /* == Region 0 == */
    /* The regions have to be alligned to FLASH_REGION0_SUBREGION_SIZE to cover the AHB Flash Region. */
    SPM_ASSERT(memory_regions.non_secure_partition_base >= NS_ROM_ALIAS_BASE);
    SPM_ASSERT(((memory_regions.non_secure_partition_base - NS_ROM_ALIAS_BASE) % QSPI_FLASH_REGION0_SUBREGION_SIZE) == 0);
    SPM_ASSERT(((memory_regions.non_secure_partition_limit - NS_ROM_ALIAS_BASE +1) % QSPI_FLASH_REGION0_SUBREGION_SIZE) == 0);

    ns_region_start_id = (memory_regions.non_secure_partition_base - NS_ROM_ALIAS_BASE)/QSPI_FLASH_REGION0_SUBREGION_SIZE;
    ns_region_end_id = (memory_regions.non_secure_partition_limit - NS_ROM_ALIAS_BASE + 1)/QSPI_FLASH_REGION0_SUBREGION_SIZE;

    /* Set to non-secure and non-privileged user access allowed */
    for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++) /* == Region 0 == */
    {
        if(ns_region_id < 8)
        {
            /* Set regions in the AHB controller for flash memory 0x0800 0000 - 0x081F FFFF */
            AHB_SECURE_CTRL->FLEXSPI0_REGION0_MEM_RULE[0] &= ~(0xF << (ns_region_id*4));
        }
        else if((ns_region_id >= 8) && (ns_region_id < 16))
        {
            /* Set regions in the AHB controller for flash memory 0x0820 0000 - 0x083F FFFF */
            AHB_SECURE_CTRL->FLEXSPI0_REGION0_MEM_RULE[1] &= ~(0xF << ((ns_region_id-8)*4));
        }else if((ns_region_id >= 16) && (ns_region_id < 24))
        {
            /* Set regions the AHB controller for flash memory 0x0840 0000 - 0x085F FFFF */
            AHB_SECURE_CTRL->FLEXSPI0_REGION0_MEM_RULE[2] &= ~(0xF << ((ns_region_id-16)*4));
        }
        else if((ns_region_id >= 24) && (ns_region_id < 32))
        {
            /* Set regions the AHB controller for flash memory 0x0860 0000 -  0x087 FFFFF */
            AHB_SECURE_CTRL->FLEXSPI0_REGION0_MEM_RULE[3] &= ~(0xF << ((ns_region_id-32)*4));
        }
        else /* == Region 1 == */
        {
            if(ns_region_start_id > QSPI_FLASH_REGION0_SUBREGION_NUMBER)
            {
                ns_region_start_id = (memory_regions.non_secure_partition_base - NS_ROM_ALIAS_BASE - QSPI_FLASH_REGION0_SIZE )/QSPI_FLASH_REGION1_SUBREGION_SIZE;
            }
            else
            {
                ns_region_start_id = 0;
            }

            ns_region_end_id = (memory_regions.non_secure_partition_limit - NS_ROM_ALIAS_BASE - QSPI_FLASH_REGION0_SIZE + 1)/QSPI_FLASH_REGION1_SUBREGION_SIZE;

            for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++)
            {
                if(ns_region_id < QSPI_FLASH_REGION1_SUBREGION_NUMBER)
                {
                    /* Set regions in the AHB controller for flash memory 0x880 0000 - 0x8FF FFFF */
                    AHB_SECURE_CTRL->FLEXSPI0_REGION1_4_MEM_RULE[0].FLEXSPI0_REGION_MEM_RULE0 &= ~(0xF << (ns_region_id*4));
                }
                else /* == Region 2 == */
                {
                    if(ns_region_start_id > QSPI_FLASH_REGION1_SUBREGION_NUMBER)
                    {
                        ns_region_start_id = (memory_regions.non_secure_partition_base - NS_ROM_ALIAS_BASE - (QSPI_FLASH_REGION0_SIZE + QSPI_FLASH_REGION1_SIZE) )/QSPI_FLASH_REGION2_SUBREGION_SIZE;
                    }
                    else
                    {
                        ns_region_start_id = 0;
                    }

                    ns_region_end_id = (memory_regions.non_secure_partition_limit - NS_ROM_ALIAS_BASE - (QSPI_FLASH_REGION0_SIZE + QSPI_FLASH_REGION1_SIZE) + 1)/QSPI_FLASH_REGION2_SUBREGION_SIZE;

                    for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++)
                    {
                        if(ns_region_id < QSPI_FLASH_REGION2_SUBREGION_NUMBER)
                        {
                            /* Set regions in the AHB controller for flash memory 0x0900 0000 - 0x9FF FFFF */
                            AHB_SECURE_CTRL->FLEXSPI0_REGION1_4_MEM_RULE[1].FLEXSPI0_REGION_MEM_RULE0 &= ~(0xF << (ns_region_id*4));
                        }
                        else/* == Region 3 == */
                        {
                            if(ns_region_start_id > QSPI_FLASH_REGION2_SUBREGION_NUMBER)
                            {
                                ns_region_start_id = (memory_regions.non_secure_partition_base - NS_ROM_ALIAS_BASE - (QSPI_FLASH_REGION0_SIZE + QSPI_FLASH_REGION1_SIZE + QSPI_FLASH_REGION2_SIZE) )/QSPI_FLASH_REGION3_SUBREGION_SIZE;
                            }
                            else
                            {
                                ns_region_start_id = 0;
                            }

                            ns_region_end_id = (memory_regions.non_secure_partition_limit - NS_ROM_ALIAS_BASE - (QSPI_FLASH_REGION0_SIZE + QSPI_FLASH_REGION1_SIZE + QSPI_FLASH_REGION2_SIZE) + 1)/QSPI_FLASH_REGION3_SUBREGION_SIZE;

                            for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++)
                            {
                                if(ns_region_id < QSPI_FLASH_REGION3_SUBREGION_NUMBER)
                                {
                                    /* Set regions in the AHB controller for flash memory 0x0A00 0000 - 0xBFF FFFF */
                                    AHB_SECURE_CTRL->FLEXSPI0_REGION1_4_MEM_RULE[2].FLEXSPI0_REGION_MEM_RULE0 &= ~(0xF << (ns_region_id*4));
                                }
                                else /* == Region 4 == */
                                {
                                    if(ns_region_start_id > QSPI_FLASH_REGION3_SUBREGION_NUMBER)
                                    {
                                        ns_region_start_id = (memory_regions.non_secure_partition_base - NS_ROM_ALIAS_BASE - (QSPI_FLASH_REGION0_SIZE + QSPI_FLASH_REGION1_SIZE + QSPI_FLASH_REGION2_SIZE + QSPI_FLASH_REGION3_SIZE) )/QSPI_FLASH_REGION4_SUBREGION_SIZE;
                                    }
                                    else
                                    {
                                        ns_region_start_id = 0;
                                    }

                                    ns_region_end_id = (memory_regions.non_secure_partition_limit - NS_ROM_ALIAS_BASE - (QSPI_FLASH_REGION0_SIZE + QSPI_FLASH_REGION1_SIZE + QSPI_FLASH_REGION2_SIZE + QSPI_FLASH_REGION3_SIZE) + 1)/QSPI_FLASH_REGION4_SUBREGION_SIZE;

                                    for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++)
                                    {
                                        if(ns_region_id < QSPI_FLASH_REGION4_SUBREGION_NUMBER)
                                        {
                                            /* Set regions in the AHB controller for flash memory 0x0C00 0000 - 0xFFF FFFF */
                                            AHB_SECURE_CTRL->FLEXSPI0_REGION1_4_MEM_RULE[3].FLEXSPI0_REGION_MEM_RULE0 &= ~(0xF << (ns_region_id*4));
                                        }
                                        else
                                        {
                                            break;
                                        }
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }

    }
#endif /* NS_QSPI_FLASH */

    /* == SRAM region == */

    /* The regions have to be alligned to 4 kB to cover the AHB RAM Region */
    SPM_ASSERT((S_DATA_SIZE % DATA_REGION0_SUBREGION_SIZE) == 0);
    SPM_ASSERT(((S_DATA_SIZE + NS_DATA_SIZE) % DATA_REGION0_SUBREGION_SIZE) == 0);

    /* Security access rules for RAM (0x3 = all regions set to secure and privileged user access*/
    AHB_SECURE_CTRL->RAM00_MEM_RULE0 = 0x00003333U; /* 0x2000_0000 - 0x2000_3FFF */
    AHB_SECURE_CTRL->RAM10_MEM_RULE0 = 0x00003333U; /* 0x2000_4000 - 0x2000_7FFF */
    AHB_SECURE_CTRL->RAM20_MEM_RULE0 = 0x00003333U; /* 0x2000_8000 - 0x2000_FFFF */
    AHB_SECURE_CTRL->RAM30_MEM_RULE0 = 0x00003333U; /* 0x2001_0000 - 0x2001_7FFF */
    AHB_SECURE_CTRL->RAM40_MEM_RULE0 = 0x00003333U; /* 0x2001_8000 - 0x2001_BFFF */

    /* SRAM memory configuration (set according to region_defs.h and flash_layout.h) */
    /* == SRAM Region 0 (0-32KB) == */
    ns_region_start_id = S_DATA_SIZE/DATA_REGION0_SUBREGION_SIZE; /* NS starts after S */
    ns_region_end_id = (S_DATA_SIZE + NS_DATA_SIZE)/DATA_REGION0_SUBREGION_SIZE;

    for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++)
    {
        /* Set regions the AHB controller for ram memory 0x2000_0000 - 0x2000_3FFF */
        if(ns_region_id < 4) {
            AHB_SECURE_CTRL->RAM00_MEM_RULE0 &= ~(0xF << (ns_region_id*4));
        }
        /* Set regions the AHB controller for ram memory 0x2000_4000 - 0x2000_7FFF */
        else if((ns_region_id >= 4) && (ns_region_id < 8)) {
                AHB_SECURE_CTRL->RAM10_MEM_RULE0 &= ~(0xF << ((ns_region_id-4)*4));
        }
        else /* == SRAM Region 1 (32KB-96KB) == */
        {
            if(ns_region_start_id > DATA_REGION0_SUBREGION_NUMBER)
            {
                ns_region_start_id = (S_DATA_SIZE - DATA_REGION0_SIZE)/DATA_REGION1_SUBREGION_SIZE;
                /* Corner case, when next sub region size is smaller */
                if((ns_region_start_id*DATA_REGION1_SUBREGION_SIZE) < (S_DATA_SIZE - DATA_REGION0_SIZE))
                {
                    ns_region_start_id++;  
                }
            }
            else
            {
                ns_region_start_id = 0;   
            }

            ns_region_end_id = (S_DATA_SIZE + NS_DATA_SIZE - DATA_REGION0_SIZE)/DATA_REGION1_SUBREGION_SIZE;
            /* Corner case, when next sub region size is smaller */
            if((ns_region_end_id*DATA_REGION1_SUBREGION_SIZE) < (S_DATA_SIZE + NS_DATA_SIZE - DATA_REGION0_SIZE))
            {
                ns_region_end_id++;  
            }
            
            for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++)
            {
                /* Set regions the AHB controller for ram memory 0x2000_8000 - 0x2000_FFFF */
                if(ns_region_id < 4) {
                    AHB_SECURE_CTRL->RAM20_MEM_RULE0 &= ~(0xF << (ns_region_id*4));
                }
                /* Set regions the AHB controller for ram memory 0x2001_0000 - 0x2001_7FFF */
                else if((ns_region_id >= 4) && (ns_region_id < 8)) {
                        AHB_SECURE_CTRL->RAM30_MEM_RULE0 &= ~(0xF << ((ns_region_id-4)*4));
                }
                else /* == SRAM Region 2 (96KB-112KB) == */
                {
                    if(ns_region_start_id > DATA_REGION1_SUBREGION_NUMBER)
                    {
                        ns_region_start_id = (uint32_t)(S_DATA_SIZE - (DATA_REGION0_SIZE + DATA_REGION1_SIZE) )/DATA_REGION2_SUBREGION_SIZE;
                    }
                    else
                    {
                        ns_region_start_id = 0;   
                    }
                    
                    ns_region_end_id = (S_DATA_SIZE + NS_DATA_SIZE - (DATA_REGION0_SIZE + DATA_REGION1_SIZE) + 1)/DATA_REGION2_SUBREGION_SIZE;
                    
                    for(ns_region_id = ns_region_start_id; ns_region_id < ns_region_end_id; ns_region_id++)
                    {
                        /* Set regions the AHB controller for ram memory 0x2008_0000 - 0x2009_FFFF  */
                        if(ns_region_id < 4) {
                            AHB_SECURE_CTRL->RAM40_MEM_RULE0 &= ~(0xF << (ns_region_id*4));
                        }
                    }
                    break;
                }
            }
            break;
        }
    }

#if TARGET_DEBUG_LOG
    SPMLOG_DBGMSG("=== [AHB MPC NS] =======\r\n");
    SPMLOG_DBGMSGVAL("NS ROM starts from : ",
                                      memory_regions.non_secure_partition_base);
    SPMLOG_DBGMSGVAL("NS ROM ends at : ",
                                      memory_regions.non_secure_partition_base +
                                     memory_regions.non_secure_partition_limit);
    SPMLOG_DBGMSGVAL("NS DATA start from : ", NS_DATA_START);
    SPMLOG_DBGMSGVAL("NS DATA ends at : ", NS_DATA_START + NS_DATA_LIMIT);
#endif

    /* Add barriers to assure the MPC configuration is done before continue
     * the execution.
     */
    __DSB();
    __ISB();

    return ARM_DRIVER_OK;
}

/*---------------------- PPC configuration functions -------------------------*/

int32_t ppc_init_cfg(void)
{
     /* Configuration of AHB Secure Controller. Grant user access to peripherals.
     * Possible values for every memory sector or peripheral rule:
     *  0    Non-secure, user access allowed.
     *  1    Non-secure, privileged access allowed.
     *  2    Secure, user access allowed.
     *  3    Secure, privileged access allowed. */
    
    /* Write access attributes for AHB_SECURE_CTRL module are tier-4 (secure privileged). */ 
    
    /* Security access rules for APB Bridge 0 peripherals. */
    AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP0_MEM_RULE0 =
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE0_SYSCON(0x0U) |                               /* System configuration */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE0_IOCON(0x0U) |                                /* I/O configuration */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE0_GPIO0(0x0U) |                                /* GPIO0 */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE0_GPIO1(0x0U) |                                /* GPIO1 */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE0_PINT0(0x0U) |                                /* PINT0 */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE0_PINT1(0x0U) |                                /* PINT1 */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE0_GINT1(0x0U);                                 /* GINT1 */

    AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP0_MEM_RULE1 =
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE1_CTIMER0(0x0U) |                              /* Standard counter/Timer 0 */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE1_CTIMER1(0x0U) |                              /* Standard counter/Timer 1 */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE1_WWDT0(0x0U) |                                /* Windowed watchdog Timer */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE1_MRT(0x0U) |                                  /* Multi-rate Timer */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE1_MICRO_TICK(0x0U) |                           /* Micro-Timer */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE1_ITRC(0x3U);                                  /* Intrusion and Tamper Response Controller (ITRC) = S */

    AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP0_MEM_RULE2 =
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE2_ANALOG_CTRL(0x0U) |                          /* Analog modules controller */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE2_eFUSE(0x0U) |                                /* eFUSE */
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE2_I3C0(0x0U);                                  /* I3C0 */
        
    AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP0_MEM_RULE3 =
        SECTRL_APB_PERIPHERAL_GROUP0_MEM_RULE3_EZH(0x0U);                                   /* EZH */

    /* Security access rules for APB Bridge 1 peripherals. */
    AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP1_MEM_RULE0 =
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE0_PMC(0x0U) |                                  /* Power Management Controller */
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE0_SYSCTL_I2S(0x0U) |                           /* SYSCTL(I2S Pin Sharing) */
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE0_SPI_MSFT(0x0U);                              /* SPI_MSFT */

    AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP1_MEM_RULE1 =
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE1_CTIMER2(0x0U) |                              /* Standard counter/Timer 2 */
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE1_CTIMER3(0x0U) |                              /* Standard counter/Timer 3 */
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE1_CTIMER4(0x0U) |                              /* Standard counter/Timer 4 */
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE1_RTC(0x0U) |                                  /* Real Time Counter */
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE1_OS_EVENT_TIMER(0x0U) |                       /* OS Event Timer */
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE1_CACHE64_POLSEL(0x0U) |                       /* CACHE64_POLSEL */
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE1_PKC(0x3U);                                   /* PKC = S */

    AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP1_MEM_RULE2 =
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE2_ELSMINI_ALIAS0(0x3U) |                     /* CSSV2MINI ALIAS0 = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE2_ELSMINI_ALIAS1(0x3U) |                     /* CSSV2MINI ALIAS1 = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE2_ELSMINI_ALIAS2(0x3U) |                     /* CSSV2MINI ALIAS2 = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE2_ELSMINI_ALIAS3(0x3U) |                     /* CSSV2MINI ALIAS3 = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE2_FLASH_CONTROLLER(0x3U) |                     /* Flash controller = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE2_PRINCE0(0x3U);                               /* PRINCE = S */

    AHB_SECURE_CTRL->APB_PERIPHERAL_GROUP1_MEM_RULE3 =
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE3_PUF_ALIAS0(0x3U) |                           /* PUF ALIAS0 = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE3_PUF_ALIAS1(0x3U) |                           /* PUF ALIAS1 = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE3_PUF_ALIAS2(0x3U) |                           /* PUF ALIAS2 = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE3_PUF_ALIAS3(0x3U) |                           /* PUF ALIAS3 = S*/
        SECTRL_APB_PERIPHERAL_GROUP1_MEM_RULE3_ROM(0x3U);                                   /* ROM = S*/

    /* Security access rules for AHB peripherals on AHB Slave Port P9*/
    AHB_SECURE_CTRL->AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0 = 
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0_DMA0(0x0U) |                       /* DMA0 */
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0_USB_FSD(0x0U) |                    /* USB */
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0_SCTIMER(0x0U) |                    /* SCT */
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0_FLEXCOMM0(0x0U) |                  /* FLEXCOMM0 */
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0_FLEXCOMM1(0x0U);                   /* FLEXCOMM1 */
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0_FLEXCOMM2(0x0U);                   /* FLEXCOMM2 */
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0_FLEXCOMM3(0x0U);                   /* FLEXCOMM3 */
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE0_FLEXCOMM4(0x0U);                   /* FLEXCOMM4 */

    AHB_SECURE_CTRL->AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE1 = 
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE1_MAILBOX(0x0U) |                    /* MAILBOX */
        SECTRL_AHB_PERIPHERAL0_SLAVE_PORT_P9_SLAVE_RULE1_GPIO(0x0U);                        /* GPIO */

    /* Security access rules for AHB peripherals on AHB Slave Port P10 */
    AHB_SECURE_CTRL->AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0 = 
        SECTRL_AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0_DMIC0(0x0U) |                         /* DMIC */
        SECTRL_AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0_CRC(0x0U) |                           /* CRC engine */
        SECTRL_AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0_FLEXCOMM5(0x0U) |                     /* FLEXCOMM5 */
        SECTRL_AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0_FLEXCOMM6(0x0U) |                     /* FLEXCOMM6 */
        SECTRL_AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0_FLEXCOMM7(0x0U) |                     /* FLEXCOMM7 */
        SECTRL_AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0_DEBUG_MAILBOX(0x0U) |                 /* DEBUG_MAILBOX */
        SECTRL_AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0_MCAN(0x0U) |                          /* MCAN */
        SECTRL_AHB_PERIPHERAL1_SLAVE_PORT_P10_SLAVE_0_HS_LSPI(0x0U);                        /* HS_LSPI */

    /* Security access rules for AHB peripherals on AHB Slave Port P11. */
    AHB_SECURE_CTRL->AHB_PERIPHERAL2_SLAVE_PORT_P11_SLAVE_RULE0 =
        SECTRL_AHB_PERIPHERAL2_SLAVE_PORT_P11_SLAVE_RULE0_ADC(0x0U) |                       /* ADC */
        SECTRL_AHB_PERIPHERAL2_SLAVE_PORT_P11_SLAVE_RULE0_CDOG(0x3U) |                      /* CDOG = S*/
        SECTRL_AHB_PERIPHERAL2_SLAVE_PORT_P11_SLAVE_RULE0_USB_FS_HOST(0x0U) |               /* USB Full Speed Host registers */
        SECTRL_AHB_PERIPHERAL2_SLAVE_PORT_P11_SLAVE_RULE0_POWERQUAD(0x0U) |                 /* POWERQUAD*/
        SECTRL_AHB_PERIPHERAL2_SLAVE_PORT_P11_SLAVE_RULE0_DMA1(0x0U) |                      /* DMA1*/
        SECTRL_AHB_PERIPHERAL2_SLAVE_PORT_P11_SLAVE_RULE0_SECGPIO(0x0U) |                   /* SECGPIO */
        SECTRL_AHB_PERIPHERAL2_SLAVE_PORT_P11_SLAVE_RULE0_AHB_SECURE(0x3U);                 /* AHB Secure Controller = S */

    /* Security access rules for AHB Secure Control Peripheral. */
    AHB_SECURE_CTRL->AHB_SECURE_CTRL_PERIPHERAL_MEM_RULE0 = 
        SECTRL_AHB_SECURE_CTRL_PERIPHERAL_MEM_RULE0_RULE0(0x3U) |                           /* Address space: 0x400A_C000 - 0x400A_CFFF */
        SECTRL_AHB_SECURE_CTRL_PERIPHERAL_MEM_RULE0_RULE1(0x3U) |                           /* Address space: 0x400A_D000 - 0x400A_DFFF */
        SECTRL_AHB_SECURE_CTRL_PERIPHERAL_MEM_RULE0_RULE2(0x3U) |                           /* Address space: 0x400A_E000 - 0x400A_EFFF */
        SECTRL_AHB_SECURE_CTRL_PERIPHERAL_MEM_RULE0_RULE3(0x3U);                            /* Address space: 0x400A_F000 - 0x400A_FFFF */

    /* Security access rules for AIPS Bridge Group 0. */
    AHB_SECURE_CTRL->AIPS_BRIDGE_GROUP0_RULE0 = 
        SECTRL_AIPS_BRIDGE_GROUP0_RULE0_ADC1(0x0U) |                                        /* ADC1 */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE0_DAC0(0x0U) |                                        /* DAC0 */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE0_HSCOMP0(0x0U) |                                     /* HSCOMP0 */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE0_OPAMP0(0x0U) |                                      /* OPAMP0 */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE0_VREF(0x0U) |                                        /* VREF */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE0_DAC1(0x0U) |                                        /* DAC1 */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE0_HSCOMP1(0x0U);                                      /* HSCOMP1 */

    AHB_SECURE_CTRL->AIPS_BRIDGE_GROUP0_RULE1 = 
        SECTRL_AIPS_BRIDGE_GROUP0_RULE1_OPAMP1(0x0U) |                                      /* OPAMP1 */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE1_DAC2(0x0U) |                                        /* DAC2 */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE1_HSCOMP2(0x0U) |                                     /* HSCOMP2 */
        SECTRL_AIPS_BRIDGE_GROUP0_RULE1_OPAMP2(0x0U);                                       /* OPAMP2 */

    /* Security access rules for AIPS Bridge Group 1 */
    AHB_SECURE_CTRL->AIPS_BRIDGE_GROUP1_RULE0 = 
        SECTRL_AIPS_BRIDGE_GROUP1_RULE0_FLEXSPI0(0x0U) |                                    /* FLEXSPI0 */
        SECTRL_AIPS_BRIDGE_GROUP1_RULE0_FLEXSPI_CMX(0x0U) |                                 /* CMX */
        SECTRL_AIPS_BRIDGE_GROUP1_RULE0_LPCAC(0x0U) |                                       /* LPCAC */
        SECTRL_AIPS_BRIDGE_GROUP1_RULE0_FLEXPWM0(0x0U) |                                    /* FLEXPWM0 */
        SECTRL_AIPS_BRIDGE_GROUP1_RULE0_ENC0(0x0U) |                                        /* ENC0 */
        SECTRL_AIPS_BRIDGE_GROUP1_RULE0_FLEXSPI_PWM1(0x0U) |                                /* FLEXSPI_PWM1 */
        SECTRL_AIPS_BRIDGE_GROUP1_RULE0_ENC1(0x0U) |                                        /* ENC1 */
        SECTRL_AIPS_BRIDGE_GROUP1_RULE0_AOI0(0x0U);                                         /* AOI0 */

    AHB_SECURE_CTRL->AIPS_BRIDGE_GROUP1_RULE1 =
        SECTRL_AIPS_BRIDGE_GROUP1_RULE1_AOI1(0x0U);                                         /* AOI1 */

    /*  TBD: 
        SEC_GPIO_MASK[3];
        SEC_GPIO_MASK3;
        SEC_GP_REG_LOCK;
        CM33_LOCK_REG[3];
   */
    /* Set PKC Security Level to secure and privileged master, and lock it. */
    AHB_SECURE_CTRL->MASTER_SEC_LEVEL = SECTRL_MASTER_SEC_LEVEL_MASTER_SEC_LEVEL_LOCK(0x1) | SECTRL_MASTER_SEC_LEVEL_PKC(0x3);
    AHB_SECURE_CTRL->MASTER_SEC_ANTI_POL_REG = ~AHB_SECURE_CTRL->MASTER_SEC_LEVEL;

    /* Enable AHB secure controller check */
    AHB_SECURE_CTRL->MISC_CTRL_REG = 
        SECTRL_MISC_CTRL_REG_WRITE_LOCK(0x2U) |                     /* 2 = Writes to this register and to the Memory and Peripheral RULE registers are allowed */
        SECTRL_MISC_CTRL_REG_ENABLE_SECURE_CHECKING (0x1U) |        /* 1 = Enable Secure Checking (restrictive mode) */
        SECTRL_MISC_CTRL_REG_ENABLE_S_PRIV_CHECK (0x2U) |           /* 2 = Disabled Secure Privilege Checking */
        SECTRL_MISC_CTRL_REG_ENABLE_NS_PRIV_CHECK (0x2U) |          /* 2 = Disabled Non-Secure Privilege Checking */
        SECTRL_MISC_CTRL_REG_DISABLE_VIOLATION_ABORT (0x2U) |       /* 2 = The violation detected by the secure checker will cause an abort. */
        SECTRL_MISC_CTRL_REG_DISABLE_STRICT_MODE (0x1U) |           /* 1 = AHB master in tier mode. Can read and write to memories at same or below level. */
        SECTRL_MISC_CTRL_DP_REG_IDAU_ALL_NS(0x2U);                  /* 2 = IDAU is enabled (restrictive mode) */
    /* Secure control duplicate register */
    AHB_SECURE_CTRL->MISC_CTRL_DP_REG = AHB_SECURE_CTRL->MISC_CTRL_REG;

    return ARM_DRIVER_OK;
}

void ppc_configure_to_secure(volatile uint32_t *bank, uint32_t pos, bool privileged)
{
    /* Clear NS flag for peripheral to prevent NS access */
    if(bank)
    {
        /*  0b00..Non-secure and Non-priviledge user access allowed.
         *  0b01..Non-secure and Privilege access allowed.
         *  0b10..Secure and Non-priviledge user access allowed.
         *  0b11..Secure and Priviledge/Non-priviledge user access allowed.
         */
        /* Set to secure and privileged user access 0x3. */
        *bank = (*bank) | (((privileged == true)?0x3:0x2) << (pos));
    }
}
