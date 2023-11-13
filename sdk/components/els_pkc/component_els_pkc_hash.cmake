# Add set(CONFIG_USE_component_els_pkc_hash true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_api_multipart_common.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_api_multipart_compute.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_api_oneshot_compute.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_core_els_sha2.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/src/mcuxClHash_internal_els_sha2.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClHash/inc
)

else()

message(SEND_ERROR "component_els_pkc_hash dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
