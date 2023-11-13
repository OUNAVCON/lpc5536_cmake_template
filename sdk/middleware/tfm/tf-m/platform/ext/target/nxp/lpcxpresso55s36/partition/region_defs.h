/*
 * Copyright (c) 2017-2022 Arm Limited. All rights reserved.
 * Copyright 2019-2022 NXP. All rights reserved.
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

#ifndef __REGION_DEFS_H__
#define __REGION_DEFS_H__

#include "flash_layout.h"

#ifdef ENABLE_HEAP
    #define S_HEAP_SIZE             (0x0000200)
#endif

#define S_MSP_STACK_SIZE        (0x0000800)
#define S_PSP_STACK_SIZE        (0x0000400)

#define NS_HEAP_SIZE            (0x0000000) /* Not used */
#define NS_STACK_SIZE           (0x00001E0)

/* This size of buffer is big enough to store an attestation
 * token produced by initial attestation service
 */
#define PSA_INITIAL_ATTEST_TOKEN_MAX_SIZE   (0x250)

#define S_IMAGE_PRIMARY_PARTITION_OFFSET (0x0)

#ifdef NS_QSPI_FLASH
    #define NS_IMAGE_PRIMARY_PARTITION_OFFSET (0x0 + QSPI_FLASH_REGION0_SUBREGION_SIZE) /* QSPI_FLASH_REGION0_SUBREGION_SIZE reserved for PS */
#else
    #define NS_IMAGE_PRIMARY_PARTITION_OFFSET (FLASH_AREA_0_OFFSET + FLASH_S_PARTITION_SIZE)
#endif

#define IMAGE_S_CODE_SIZE           (FLASH_S_PARTITION_SIZE)
#define IMAGE_NS_CODE_SIZE          (FLASH_NS_PARTITION_SIZE)

#define CMSE_VENEER_REGION_SIZE     (0x340)

/* Alias definitions for secure and non-secure areas*/
#define S_ROM_ALIAS(x)  (S_ROM_ALIAS_BASE + (x))
#define NS_ROM_ALIAS(x) (NS_ROM_ALIAS_BASE + (x))

#define S_RAM_ALIAS(x)  (S_RAM_ALIAS_BASE + (x))
#define NS_RAM_ALIAS(x) (NS_RAM_ALIAS_BASE + (x))

/* Secure regions */
#define S_IMAGE_PRIMARY_AREA_OFFSET \
             (S_IMAGE_PRIMARY_PARTITION_OFFSET)
#define S_CODE_START    (S_ROM_ALIAS(S_IMAGE_PRIMARY_AREA_OFFSET))
#define S_CODE_SIZE     (IMAGE_S_CODE_SIZE)
#define S_CODE_LIMIT    (S_CODE_START + S_CODE_SIZE - 1)

#define S_DATA_START    (S_RAM_ALIAS(0x0+RESERVED_RAM_SIZE))
#define S_DATA_SIZE     ((TOTAL_RAM_SIZE / 2)+0x4000)
#define S_DATA_LIMIT    (S_DATA_START + S_DATA_SIZE - 1)

/* Size of vector table: 136 interrupt handlers + 4 bytes MPS initial value */
#define S_CODE_VECTOR_TABLE_SIZE    (0x224)

/* Non-secure regions */
#define NS_IMAGE_PRIMARY_AREA_OFFSET \
                        (NS_IMAGE_PRIMARY_PARTITION_OFFSET)
#define NS_CODE_START   (NS_ROM_ALIAS(NS_IMAGE_PRIMARY_AREA_OFFSET))
#define NS_CODE_SIZE    (IMAGE_NS_CODE_SIZE)
#define NS_CODE_LIMIT   (NS_CODE_START + NS_CODE_SIZE - 1)

#define NS_DATA_START   (NS_RAM_ALIAS(S_DATA_SIZE+RESERVED_RAM_SIZE))
#define NS_DATA_SIZE    (TOTAL_RAM_SIZE - S_DATA_SIZE)
#define NS_DATA_LIMIT   (NS_DATA_START + NS_DATA_SIZE - 1)

/* Flash is divided into 32 kB sub-regions. Each sub-region can be assigned individual
security tier by programing corresponding registers in secure AHB controller.*/
#define FLASH_SUBREGION_SIZE    (0x8000)     /* 32 kB */


/* FlexSPI. Each sub-region can be assigned individual
security tier by programing corresponding registers in secure AHB controller.*/
/* Region 0: 8 MB (32 * 256 KB). */
#define QSPI_FLASH_REGION0_SUBREGION_NUMBER  (32)  
#define QSPI_FLASH_REGION0_SUBREGION_SIZE    (1024 * 256)            /* 256 kB */
#define QSPI_FLASH_REGION0_SIZE              (QSPI_FLASH_REGION0_SUBREGION_NUMBER * QSPI_FLASH_REGION0_SUBREGION_SIZE)     /* 8 MB */
/* Region 1: 8 MB (4 * 2 MB) */
#define QSPI_FLASH_REGION1_SUBREGION_NUMBER  (4)  
#define QSPI_FLASH_REGION1_SUBREGION_SIZE    (1024 * 1024 * 2)       /* 2 MB */
#define QSPI_FLASH_REGION1_SIZE              (QSPI_FLASH_REGION1_SUBREGION_NUMBER * QSPI_FLASH_REGION1_SUBREGION_SIZE)     /* 8 MB */
/* Region 2: 16 MB (4 * 4 MB) */
#define QSPI_FLASH_REGION2_SUBREGION_NUMBER  (4)  
#define QSPI_FLASH_REGION2_SUBREGION_SIZE    (1024 * 1024 * 4)       /* 4 MB */
#define QSPI_FLASH_REGION2_SIZE              (QSPI_FLASH_REGION2_SUBREGION_NUMBER * QSPI_FLASH_REGION2_SUBREGION_SIZE)     /* 16 MB */
/* Region 3: 32 MB (4 * 8 MB) */
#define QSPI_FLASH_REGION3_SUBREGION_NUMBER  (4)  
#define QSPI_FLASH_REGION3_SUBREGION_SIZE    (1024 * 1024 * 8)       /* 8 MB */
#define QSPI_FLASH_REGION3_SIZE              (QSPI_FLASH_REGION3_SUBREGION_NUMBER * QSPI_FLASH_REGION3_SUBREGION_SIZE)     /* 32 MB */
/* Region 4: 64 MB (4 * 16 MB) */
#define QSPI_FLASH_REGION4_SUBREGION_NUMBER  (4)  
#define QSPI_FLASH_REGION4_SUBREGION_SIZE    (1024 * 1024 * 16)      /* 16 MB */
#define QSPI_FLASH_REGION4_SIZE              (QSPI_FLASH_REGION4_SUBREGION_NUMBER * QSPI_FLASH_REGION4_SUBREGION_SIZE)     /* 64 MB */


/* RAM. Each sub-region can be assigned individual
security tier by programing corresponding registers in secure AHB controller. */

/* Region 0: SRAM0 to SRAM1 32 KB, (8 * 4 KB) */
#define DATA_REGION0_SUBREGION_NUMBER   (8)      
#define DATA_REGION0_SUBREGION_SIZE     (1024*4)      /* 4 KB*/
#define DATA_REGION0_SIZE               (DATA_REGION0_SUBREGION_NUMBER * DATA_REGION0_SUBREGION_SIZE)      /* 32 KB */
/* Region 1: SRAM2 to SRAM3 64 KB, (8 * 8 KB) */
#define DATA_REGION1_SUBREGION_NUMBER   (8)      
#define DATA_REGION1_SUBREGION_SIZE     (1024 * 8)  /* 8 KB*/
#define DATA_REGION1_SIZE               (DATA_REGION1_SUBREGION_NUMBER * DATA_REGION1_SUBREGION_SIZE)      /* 64 KB */
/* Region 2: SRAM4 16 KB, (1 * 4 KB) */
#define DATA_REGION2_SUBREGION_NUMBER   (4)      
#define DATA_REGION2_SUBREGION_SIZE     (1024 * 4)  /* 4 KB*/
#define DATA_REGION2_SIZE               (DATA_REGION2_SUBREGION_NUMBER * DATA_REGION2_SUBREGION_SIZE)      /* 16 KB */


/* NS partition information is used for MPC and SAU configuration */
#define NS_PARTITION_START              (NS_ROM_ALIAS(NS_IMAGE_PRIMARY_PARTITION_OFFSET))
#define NS_PARTITION_SIZE               (FLASH_NS_PARTITION_SIZE)

/* Code SRAM area */
#define S_RAM_CODE_SIZE                 (0x4000) /* SRAM X region */
#define S_RAM_CODE_START                (0x14000000)
#define NS_RAM_CODE_START               (0x04000000)

/* Shared data area between bootloader and runtime firmware.
 * Shared data area is allocated at the beginning of the RAM, it is overlapping
 * with TF-M Secure code's MSP stack
 */
#define BOOT_TFM_SHARED_DATA_BASE S_RAM_ALIAS_BASE
#define BOOT_TFM_SHARED_DATA_SIZE (0x400)
#define BOOT_TFM_SHARED_DATA_LIMIT (BOOT_TFM_SHARED_DATA_BASE + \
                                    BOOT_TFM_SHARED_DATA_SIZE - 1)

#endif /* __REGION_DEFS_H__ */
