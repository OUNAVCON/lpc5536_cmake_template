# Add set(CONFIG_USE_component_els_pkc_mac_modes true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_mac)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_ELS_Functions.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_ELS_CBCMAC.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_ELS_CMAC.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_ELS_HMAC.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_Helper.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/src/mcuxClMacModes_Modes.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClMacModes/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_mac_modes dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
