# Add set(CONFIG_USE_component_els_pkc_cipher_modes true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_cipher)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/src/mcuxClCipherModes_ELS_Aes.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/src/mcuxClCipherModes_ELS_EngineAes.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Helper.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/src/mcuxClCipherModes_Modes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClCipherModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_cipher_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
