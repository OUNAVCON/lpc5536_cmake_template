var a00041 =
[
    [ "nboot_secure_counter_t", "a00041.html#a00393", null ],
    [ "nboot_context_t", "a00041.html#a00382", [
      [ "totalBlocks", "a00041.html#a561f4115a69e3abe62664d27fbd45b08", null ],
      [ "processData", "a00041.html#a7b0ea3fa99db265b67ef0bfbcaf30162", null ],
      [ "timeout", "a00041.html#a3cf9c69e0a91f8c785b34dbb5f6cb7a8", null ],
      [ "keyinfo", "a00041.html#a5a05d70b7f86ad955f0e4ead005e6780", null ],
      [ "context", "a00041.html#a55629a1d1ea1bc7e84c6e91433ac226c", null ],
      [ "uuid", "a00041.html#a97588aae2abad3842096970c6cca3f8d", null ],
      [ "prngReadyFlag", "a00041.html#a74cd6f02ca1a0b7280e20aad72931297", null ],
      [ "oemShareValidFlag", "a00041.html#a617fd131239026dc8e8cb1ce8350680c", null ],
      [ "oemShare", "a00041.html#a227173e7640aff9e996cb2cf3e4a0adc", null ],
      [ "secureCounter", "a00041.html#a34c5f85add974876be320c396c3f749a", null ]
    ] ],
    [ "nboot_rot_auth_parms_t", "a00041.html#a00390", [
      [ "soc_rootKeyRevocation", "a00041.html#ae33d35f3a0c089db932ee9382d3cb1fa", null ],
      [ "soc_imageKeyRevocation", "a00041.html#ae80b10f512cd17c20e3a57a33f1b7343", null ],
      [ "soc_rkh", "a00041.html#aa36b471a1691b4160b2c0720d918cfd1", null ],
      [ "soc_numberOfRootKeys", "a00041.html#a891bdbd4338601887c0d8e9aef95e5d1", null ],
      [ "soc_rootKeyUsage", "a00041.html#a44322351fe4f20a8042ea6bd7d5558fd", null ],
      [ "soc_rootKeyTypeAndLength", "a00041.html#a7b9f30ff436035b9c44dd3fbf07d474c", null ]
    ] ],
    [ "nboot_sb3_load_manifest_parms_t", "a00041.html#a00392", [
      [ "soc_RoTNVM", "a00041.html#ad9511ed08b95028453b29d1b3d3e28cd", null ],
      [ "soc_trustedFirmwareVersion", "a00041.html#a982d3e212a5ce439a5eddc1cd3119f7b", null ]
    ] ],
    [ "nboot_img_auth_ecdsa_parms_t", "a00041.html#a00386", [
      [ "soc_RoTNVM", "a00041.html#a5ae6dacff634f9a495a1790f3bf35652", null ],
      [ "soc_trustedFirmwareVersion", "a00041.html#a58323e23f410e8604f924b0698adce22", null ]
    ] ],
    [ "nboot_img_authenticate_cmac_parms_t", "a00041.html#a00387", [
      [ "expectedMAC", "a00041.html#a1425967d7719fa89d4781a642ab2f8d6", null ]
    ] ],
    [ "NXPCLHASH_WA_SIZE_MAX", "a00041.html#ga0690e3c322cf407d1f3028335cf5c276", null ],
    [ "NXPCLCSS_HASH_RTF_OUTPUT_SIZE_HAL", "a00041.html#ga4d297699b1573f2089b57774f14039e1", null ],
    [ "kNBOOT_RootKeyUsage_DebugCA_ImageCA_FwCA_ImageKey_FwKey", "a00041.html#gadcc394697a2295209637a53aaa7bda57", null ],
    [ "kNBOOT_RootKey_Enabled", "a00041.html#ga70b83e45d9ee91e872f104b0017c3f0e", null ],
    [ "kNBOOT_RootKey_Ecdsa_P256", "a00041.html#ga9e591c731eb92faaf44cd10cdf546d77", null ],
    [ "nboot_lc_nxpBlank", "a00041.html#ga93c7f5d04732a658e6b7065655dc29ca", null ],
    [ "nboot_status_t", "a00041.html#gaf2de98ef664399f28cda396f075307af", null ],
    [ "nboot_status_protected_t", "a00041.html#ga9ac404fa8812d6f22b68204897ca642d", [
      [ "kStatus_NBOOT_Success", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa5f3d577492ce2979cc2a4563efc6ef56", null ],
      [ "kStatus_NBOOT_Fail", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5faef44fd6552d67e8646edf3b2f8ad7092", null ],
      [ "kStatus_NBOOT_InvalidArgument", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa76619174d07bfc1e40028f6542426d75", null ],
      [ "kStatus_NBOOT_RequestTimeout", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa5a33959374e9b89e22cc262a6d5edace", null ],
      [ "kStatus_NBOOT_KeyNotLoaded", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa71c2aa6197743fecb1a825b26dc4b63d", null ],
      [ "kStatus_NBOOT_AuthFail", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa723d50e929965efd95c480dfcd08c369", null ],
      [ "kStatus_NBOOT_OperationNotAvaialable", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa353f8c689722e880d7313dc6bef03e05", null ],
      [ "kStatus_NBOOT_KeyNotAvailable", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa0775c7d59bb7eb0cf19491de8ce006f7", null ],
      [ "kStatus_NBOOT_IvCounterOverflow", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa04bd7a5d0c859f6990d38b5107b11d76", null ],
      [ "kStatus_NBOOT_SelftestFail", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fadb23639c65f62e62d62fb35d4b02b3fa", null ],
      [ "kStatus_NBOOT_InvalidDataFormat", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa642bd3e09b72d71cdb014e333c6b0157", null ],
      [ "kStatus_NBOOT_IskCertUserDataTooBig", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fa470a3025e7140f7cc0e4f1d4d80fc89d", null ],
      [ "kStatus_NBOOT_IskCertSignatureOffsetTooSmall", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fadac5ea2c9bca6dcdb15794ad12e9d0ac", null ],
      [ "kStatus_NBOOT_MemcpyFail", "a00041.html#gga394b3903fbf00ba2b6243f60689a5a5fae60ebc0e9ae2f0010152d375a6607b73", null ]
    ] ],
    [ "nboot_bool_t", "a00041.html#gaf724509c6c44b6a93eff830879a025cc", [
      [ "kNBOOT_TRUE", "a00041.html#ggaf724509c6c44b6a93eff830879a025cca4aba5e8a367c6911a04d776fd3c2a4d1", null ],
      [ "kNBOOT_TRUE256", "a00041.html#ggaf724509c6c44b6a93eff830879a025cca955841f58c1ef47dfa75b946f0d878fb", null ],
      [ "kNBOOT_TRUE384", "a00041.html#ggaf724509c6c44b6a93eff830879a025cca4a77b251d38654d6e66753f3cc5bd874", null ],
      [ "kNBOOT_FALSE", "a00041.html#ggaf724509c6c44b6a93eff830879a025cca135ec05f5d840f3207cdcdfc9bf944c4", null ]
    ] ],
    [ "NBOOT_GenerateRandom", "a00041.html#ga9da0c7767a8fc77dd30299ae7562dfff", null ],
    [ "NBOOT_ContextInit", "a00041.html#gac60805d1c384b40d1f776fbec95f640f", null ],
    [ "NBOOT_ContextDeinit", "a00041.html#gae9dfcd2064e767fde1e00935d3c24507", null ],
    [ "NBOOT_Sb3LoadManifest", "a00041.html#gafdea6c80ab6ef557141abb50031d39dc", null ],
    [ "NBOOT_Sb3LoadBlock", "a00041.html#ga0b82281194699996bfd3e0e0c9c45947", null ],
    [ "NBOOT_ImgAuthenticateEcdsa", "a00041.html#gaf9615d2af761538e58e773deba26b307", null ],
    [ "NBOOT_ImgAuthenticateCmac", "a00041.html#ga5fb12fadd9a1d497c3564ba1845dece5", null ]
];