# Add set(CONFIG_USE_middleware_azure_rtos_nxd true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_middleware_azure_rtos_nxd_template AND CONFIG_USE_middleware_azure_rtos_fx)

else()

message(SEND_ERROR "middleware_azure_rtos_nxd dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
