# Add set(CONFIG_USE_middleware_ntag_i2c_plus true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/HAL_NTAG/ntag_bridge.c
  ${CMAKE_CURRENT_LIST_DIR}/HAL_NTAG/ntag_driver.c
  ${CMAKE_CURRENT_LIST_DIR}/HAL_I2C/i2c_kinetis_fsl.c
  ${CMAKE_CURRENT_LIST_DIR}/HAL_ISR/isr_common.c
  ${CMAKE_CURRENT_LIST_DIR}/HAL_ISR/isr_kinetis.c
  ${CMAKE_CURRENT_LIST_DIR}/HAL_TMR/timer_driver.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/HAL_NTAG/inc
  ${CMAKE_CURRENT_LIST_DIR}/HAL_NTAG
  ${CMAKE_CURRENT_LIST_DIR}/HAL_I2C/inc
  ${CMAKE_CURRENT_LIST_DIR}/HAL_ISR/inc
  ${CMAKE_CURRENT_LIST_DIR}/HAL_ISR
  ${CMAKE_CURRENT_LIST_DIR}/HAL_TMR/inc
  ${CMAKE_CURRENT_LIST_DIR}/inc
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DHAVE_STDBOOL_H
    -DHAVE_STDINT_H
  )

endif()

