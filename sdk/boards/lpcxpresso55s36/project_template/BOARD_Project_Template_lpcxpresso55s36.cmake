# Add set(CONFIG_USE_BOARD_Project_Template_lpcxpresso55s36 true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_BOARD STREQUAL lpcxpresso55s36) AND CONFIG_USE_component_usart_adapter AND (CONFIG_DEVICE_ID STREQUAL LPC55S36) AND CONFIG_USE_device_LPC55S36_startup AND CONFIG_USE_driver_clock AND CONFIG_USE_driver_flexcomm_i2c AND CONFIG_USE_driver_flexcomm_usart AND CONFIG_USE_driver_lpc_gpio AND CONFIG_USE_driver_lpc_iocon AND CONFIG_USE_driver_power AND CONFIG_USE_driver_reset AND ((CONFIG_USE_component_serial_manager AND CONFIG_USE_utility_assert AND CONFIG_USE_utility_debug_console) OR (CONFIG_USE_utility_assert_lite AND CONFIG_USE_utility_debug_console_lite)))

add_config_file(${CMAKE_CURRENT_LIST_DIR}/board.h "" BOARD_Project_Template_lpcxpresso55s36)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/board.c "" BOARD_Project_Template_lpcxpresso55s36)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/clock_config.h ${CMAKE_CURRENT_LIST_DIR}/. BOARD_Project_Template_lpcxpresso55s36)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/clock_config.c "" BOARD_Project_Template_lpcxpresso55s36)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/pin_mux.h ${CMAKE_CURRENT_LIST_DIR}/. BOARD_Project_Template_lpcxpresso55s36)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/pin_mux.c "" BOARD_Project_Template_lpcxpresso55s36)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/peripherals.h ${CMAKE_CURRENT_LIST_DIR}/. BOARD_Project_Template_lpcxpresso55s36)
add_config_file(${CMAKE_CURRENT_LIST_DIR}/peripherals.c "" BOARD_Project_Template_lpcxpresso55s36)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "BOARD_Project_Template_lpcxpresso55s36 dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
