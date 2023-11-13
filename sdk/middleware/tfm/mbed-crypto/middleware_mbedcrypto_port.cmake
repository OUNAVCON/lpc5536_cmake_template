# Add set(CONFIG_USE_middleware_mbedcrypto_port true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_USE_component_els_pkc_platform_lpc AND (CONFIG_DEVICE_ID STREQUAL LPC55S36)))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/port/mbedcrypto_mcux_casper.c
  ${CMAKE_CURRENT_LIST_DIR}/port/mbedcrypto_mcux_els.c
  ${CMAKE_CURRENT_LIST_DIR}/port/mbedcrypto_mcux_hashcrypt.c
  ${CMAKE_CURRENT_LIST_DIR}/port/mbedcrypto_mcux_entropy.c
  ${CMAKE_CURRENT_LIST_DIR}/port/mbedcrypto_mcux_pkc.c
  ${CMAKE_CURRENT_LIST_DIR}/port/mbedcrypto_mcux_sss.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/port
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DCRYPTO_HW_ACCELERATOR
    -DMBEDTLS_CONFIG_FILE="mbedcrypto_mcux_config.h"
  )

endif()

else()

message(SEND_ERROR "middleware_mbedcrypto_port dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
