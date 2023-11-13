# Add set(CONFIG_USE_component_els_pkc_pkc true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_ecc AND CONFIG_USE_component_els_pkc_math AND CONFIG_USE_component_els_pkc_rsa)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/src/mcuxClPkc_Calculate.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/src/mcuxClPkc_ImportExport.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/src/mcuxClPkc_Initialize.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/src/mcuxClPkc_UPTRT.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClPkc/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_pkc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
