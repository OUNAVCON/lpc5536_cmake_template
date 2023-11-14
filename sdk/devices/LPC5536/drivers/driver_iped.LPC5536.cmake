# Add set(CONFIG_USE_driver_iped true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC5536) AND CONFIG_USE_driver_common AND CONFIG_USE_component_els_pkc AND CONFIG_USE_driver_flashiap AND CONFIG_USE_driver_mem_interface)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/fsl_iped.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "driver_iped.LPC5536 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
