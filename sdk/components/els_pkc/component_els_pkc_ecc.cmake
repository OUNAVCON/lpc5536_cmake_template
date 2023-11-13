# Add set(CONFIG_USE_component_els_pkc_ecc true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_secure_counter AND CONFIG_USE_component_els_pkc_pre_processor AND CONFIG_USE_component_els_pkc_key AND CONFIG_USE_component_els_pkc_els)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Constants.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateKeyPair.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateKeyPair_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignature.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignature_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_GenerateSignatureMode.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_InitPrivKeyInputMode.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_CalcHashModN.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_CalcHashModN_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_DecodePoint_Ed25519.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_DecodePoint_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_Internal_SignatureMechanisms.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_EdDSA_VerifySignature.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_BlindedScalarMult.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_Convert_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_GenerateMultiplicativeBlinding.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_Interleave_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_InterleaveScalar.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_InterleaveTwoScalars.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_PointComparison_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_RecodeAndReorderScalar.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_SetupEnvironment_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Internal_Types.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_KeyTypes.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_DhKeyAgreement.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_DhKeyGeneration.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_DhSetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_MontDhX.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_MontDhX_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_SecureScalarMult_XZMontLadder.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Mont_Internal_SecureScalarMult_XZMontLadder_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_SignatureMechanisms.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_FixScalarMult.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PlainFixScalarMult25519.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PlainPtrSelectComb.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PlainPtrSelectML.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PlainVarScalarMult.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PointArithmeticEd25519.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PointArithmeticEd25519_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PointSubtraction_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PointValidation_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_PrecPointImportAndValidate.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_VarScalarMult.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_TwEd_Internal_VarScalarMult_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_ConvertPoint_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_KeyGen.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_KeyGen_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointArithmetic.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointArithmetic_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointCheck.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointCheck_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_PointMult.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_SecurePointMult_CoZMontLadder.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_SecurePointMult_CoZMontLadder_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Internal_SetupEnvironment.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_KeyGen.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_PointMult.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_PointMult_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Sign.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Sign_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Verify.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_Weier_Verify_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_GenerateCustomKeyType.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_GenerateDomainParams.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_GenerateDomainParams_FUP.c
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/src/mcuxClEcc_WeierECC_Internal_SetupEnvironment.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClEcc/inc/internal
)

else()

message(SEND_ERROR "component_els_pkc_ecc dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
