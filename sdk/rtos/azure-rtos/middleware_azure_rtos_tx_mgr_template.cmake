# Add set(CONFIG_USE_middleware_azure_rtos_tx_mgr_template true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/threadx/ports/common/tx_initialize_low_level.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/threadx/common/inc
  ${CMAKE_CURRENT_LIST_DIR}/threadx/common_modules/inc
  ${CMAKE_CURRENT_LIST_DIR}/threadx/common_modules/module_manager/inc
)

if(CONFIG_USE_COMPONENT_CONFIGURATION)
  message("===>Import configuration from ${CMAKE_CURRENT_LIST_FILE}")

  target_compile_definitions(${MCUX_SDK_PROJECT_NAME} PUBLIC
    -DTX_INCLUDE_USER_DEFINE_FILE
    -DFSL_RTOS_THREADX
  )

endif()

