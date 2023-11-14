# Add set(CONFIG_USE_driver_prince true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc AND CONFIG_USE_driver_mem_interface AND (CONFIG_DEVICE_ID STREQUAL LPC5536) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/fsl_prince.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DFFR_INCLUDE="fsl_flash_ffr.h"
  )

endif()

else()

message(SEND_ERROR "driver_prince.LPC5536 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
