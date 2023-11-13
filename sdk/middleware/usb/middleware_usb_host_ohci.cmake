# Add set(CONFIG_USE_middleware_usb_host_ohci true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC5534 OR CONFIG_DEVICE_ID STREQUAL LPC5536 OR CONFIG_DEVICE_ID STREQUAL LPC55S36) AND CONFIG_USE_middleware_usb_host_ohci_config_header AND CONFIG_USE_middleware_usb_host_common_header)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/host/usb_host_ohci.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/host
  ${CMAKE_CURRENT_LIST_DIR}/include
)

else()

message(SEND_ERROR "middleware_usb_host_ohci dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
