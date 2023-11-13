# Add set(CONFIG_USE_component_els_pkc_aead_modes true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_aead)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_ELS_AesCcm.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_ELS_AesGcm.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_ELS_CcmEngineAes.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_ELS_Constants.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_ELS_GcmEngineAes.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_ELS_MultiPart.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/src/mcuxClAeadModes_ELS_OneShot.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClAeadModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_aead_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
