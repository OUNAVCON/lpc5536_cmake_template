# Add set(CONFIG_USE_component_els_pkc_examples true) in config.cmake to use this component

include_guard(GLOBAL)
message("${CMAKE_CURRENT_LIST_FILE} component is included.")

if(CONFIG_USE_component_els_pkc_flow_protection AND CONFIG_USE_component_els_pkc_session AND CONFIG_USE_component_els_pkc_memory AND CONFIG_USE_component_els_pkc_els AND CONFIG_USE_component_els_pkc_pkc AND CONFIG_USE_component_els_pkc)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClAeadModes/mcuxClAeadModes_multiPart_ELS_CCM_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClAeadModes/mcuxClAeadModes_oneshot_ELS_CCM_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClAeadModes/mcuxClAeadModes_oneshot_ELS_GCM_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_CBC_Multipart_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_CBC_Oneshot_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_CBC_Oneshot_ZeroPadding_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_CTR_Multipart_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_CTR_Oneshot_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_ECB_Multipart_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_ECB_Oneshot_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_ECB_Oneshot_ZeroPadding_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_ECB_Multipart_PaddingPKCS7_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClCipherModes/mcuxClCipherModes_ECB_Oneshot_PaddingPKCS7_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_GenerateKeyPair_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_GenerateSignature_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_VerifySignature_Ed25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_Mont_Curve25519_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_WeierECC_CustomEccWeierType_BN256_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ctx_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEcc/mcuxClEcc_EdDSA_Ed25519ph_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Cipher_Aes128_Cbc_Encrypt_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Cipher_Aes128_Ecb_Encrypt_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Common_Get_Info_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Ecc_Keygen_Sign_Verify_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Hash_Sha224_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Hash_Sha256_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Hash_Sha384_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Hash_Sha512_One_Block_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Rng_Prng_Get_Random_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClEls/mcuxClEls_Tls_Master_Key_Session_Keys_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHash/mcuxClHash_sha224_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHash/mcuxClHash_sha256_longMsgOneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHash/mcuxClHash_sha256_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHash/mcuxClHash_sha256_streaming_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHash/mcuxClHash_sha384_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClHash/mcuxClHash_sha512_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClKey/mcuxClKey_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClMacModes/mcuxClMacModes_cbc_mac_multipart_zero_padding_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClMacModes/mcuxClMacModes_cbc_mac_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClMacModes/mcuxClMacModes_cmac_oneshot_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClMacModes/mcuxClMacModes_hmac_oneshot_external_key_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRandomModes/mcuxClRandomModes_ELS_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRsa/mcuxClRsa_sign_NoEncode_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRsa/mcuxClRsa_sign_pss_sha2_256_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRsa/mcuxClRsa_verify_NoVerify_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxClRsa/mcuxClRsa_verify_pssverify_sha2_256_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslFlowProtection/mcuxCsslFlowProtection_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/data_invariant_memory_compare.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/data_invariant_memory_copy.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/mcuxCsslMemory_Clear_example.c
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/mcuxCsslMemory_Set_example.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslFlowProtection/inc
  ${CMAKE_CURRENT_LIST_DIR}/examples/mcuxCsslMemory/inc
  ${CMAKE_CURRENT_LIST_DIR}/src/comps/mcuxClExample/inc
)

else()

message(SEND_ERROR "component_els_pkc_examples dependency does not meet, please check ${CMAKE_CURRENT_LIST_FILE}.")

endif()
