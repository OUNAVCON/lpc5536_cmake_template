# Add set(CONFIG_USE_middleware_motor_control_mc_drivers_lpcadc_pwma_enc true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if((CONFIG_DEVICE_ID STREQUAL LPC55S36))

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_drivers/mcdrv_adc_lpc55s36.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_drivers/mcdrv_eflexpwm_lpc.c
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_drivers/mcdrv_enc_qd.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/pmsm/pmsm_float/mc_drivers
)

else()

message(SEND_ERROR "middleware_motor_control_mc_drivers_lpcadc_pwma_enc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
