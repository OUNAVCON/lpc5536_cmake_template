# Add set(CONFIG_USE_component_els_pkc_els true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_els_header_only AND CONFIG_USE_component_els_pkc_els_common AND CONFIG_USE_component_els_pkc_standalone_keyManagement AND CONFIG_USE_component_els_pkc_standalone_gdet AND CONFIG_USE_component_els_pkc_hash AND CONFIG_USE_component_els_pkc_core AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_mac_modes AND CONFIG_USE_component_els_pkc_aead_modes AND CONFIG_USE_component_els_pkc_cipher_modes)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Aead.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Cipher.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Cmac.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Crc.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Ecc.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Hash.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Hmac.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Kdf.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEls/src/mcuxClEls_Rng.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
)

else()

message(SEND_ERROR "component_els_pkc_els dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
