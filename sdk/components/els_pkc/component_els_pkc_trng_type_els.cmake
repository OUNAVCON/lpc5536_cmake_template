# Add set(CONFIG_USE_component_els_pkc_trng_type_els true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_trng AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClTrng/src/mcuxClTrng_ELS.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "component_els_pkc_trng_type_els dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
