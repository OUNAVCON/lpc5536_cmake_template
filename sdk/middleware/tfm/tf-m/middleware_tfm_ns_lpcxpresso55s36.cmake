# Add set(CONFIG_USE_middleware_tfm_ns_lpcxpresso55s36 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL lpcxpresso55s36))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/platform/ext/target/nxp/lpcxpresso55s36
  ${CMAKE_CURRENT_LIST_DIR}/platform/ext/target/nxp/lpcxpresso55s36/partition
  ${CMAKE_CURRENT_LIST_DIR}/platform/ext/target/nxp/lpcxpresso55s36/Device/Include
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTARGET_CONFIG_HEADER_FILE="config_tfm_target.h"
  )

endif()

else()

message(SEND_ERROR "middleware_tfm_ns_lpcxpresso55s36 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
