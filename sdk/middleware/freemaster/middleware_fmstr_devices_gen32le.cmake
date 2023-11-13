# Add set(CONFIG_USE_middleware_fmstr_devices_gen32le true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC5534 OR CONFIG_DEVICE_ID STREQUAL LPC5536 OR CONFIG_DEVICE_ID STREQUAL LPC55S36))

else()

message(SEND_ERROR "middleware_fmstr_devices_gen32le dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
