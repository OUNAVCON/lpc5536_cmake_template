# Add set(CONFIG_USE_component_els_pkc true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_trng AND ((CONFIG_USE_component_els_pkc_platform_lpc AND CONFIG_USE_component_els_pkc_static_lib_lpc AND (CONFIG_DEVICE_ID STREQUAL LPC55S36))))

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/inc/impl
)

else()

message(SEND_ERROR "component_els_pkc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
