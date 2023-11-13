# Add set(CONFIG_USE_component_els_pkc_memory true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_param_integrity AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_toolchain)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMemory/src/mcuxClMemory.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Clear.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Compare.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Copy.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/src/mcuxCsslMemory_Set.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxCsslMemory/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_memory dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
