# Add set(CONFIG_USE_driver_opamp true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC55S36) AND CONFIG_USE_driver_common)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/fsl_opamp.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "driver_opamp.LPC55S36 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
