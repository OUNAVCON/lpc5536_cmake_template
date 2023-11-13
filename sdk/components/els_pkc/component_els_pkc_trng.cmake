# Add set(CONFIG_USE_component_els_pkc_trng true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_trng dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
