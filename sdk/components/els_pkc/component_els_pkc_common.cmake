# Add set(CONFIG_USE_component_els_pkc_common true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_memory)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/common/inc
)

else()

message(SEND_ERROR "component_els_pkc_common dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
