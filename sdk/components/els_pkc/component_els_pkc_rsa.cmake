# Add set(CONFIG_USE_component_els_pkc_rsa true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_toolchain)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_ComputeD.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_ComputeD_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_GenerateProbablePrime.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Crt.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Crt_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_KeyGeneration_Plain.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Mgf1.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_MillerRabinTest.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_MillerRabinTest_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_ModInv.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_NoEncode.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_NoVerify.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Encode_sign.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Pkcs1v15Verify.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PrivateCrt.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PrivateCrt_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PrivatePlain.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PssEncode.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_PssVerify.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Public.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Public_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Sign.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_TestPQDistance.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_TestPQDistance_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_TestPrimeCandidate.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_TestPrimeCandidate_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_Verify.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_VerifyE.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_RemoveBlinding.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/src/mcuxClRsa_RemoveBlinding_FUP.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClRsa/inc
)

else()

message(SEND_ERROR "component_els_pkc_rsa dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
