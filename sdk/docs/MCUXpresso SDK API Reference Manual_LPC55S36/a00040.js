var a00040 =
[
    [ "nboot_sb3_header_t", "a00040.html#a00391", [
      [ "magic", "a00040.html#ad633b0853104a02ad72aac24bb80a1a0", null ],
      [ "formatVersion", "a00040.html#a8b6b468c2f2c23360bf734f14c75cd28", null ],
      [ "flags", "a00040.html#aa7bf9969ede6f4ecd6049269e8bc0874", null ],
      [ "blockCount", "a00040.html#aae366a54ac5379d4a55e30e7bee83bfb", null ],
      [ "blockSize", "a00040.html#af5a8a4643c6892be71052cfe3e7d41f4", null ],
      [ "timeStamp", "a00040.html#a321137c3073e075b3ff1c81e1faed08a", null ],
      [ "firmwareVersion", "a00040.html#aef049cd0929b11d6ec9917f6c3c03268", null ],
      [ "imageTotalLength", "a00040.html#a70ae917af717b9c965fd847ac4221ad4", null ],
      [ "imageType", "a00040.html#a15cd732fb16df2c8cf14378ff8d8ade7", null ],
      [ "certificateBlockOffset", "a00040.html#abfe2cc93f2d8d47936438081e33493d9", null ],
      [ "description", "a00040.html#a87aa844261ea6376672e9c8ac1bdf396", null ]
    ] ],
    [ "nboot_certificate_header_block_t", "a00040.html#a00381", [
      [ "magic", "a00040.html#af130388a75edf043ff9306c20aec003c", null ],
      [ "formatMajorMinorVersion", "a00040.html#a10d905cffc630cfe7ae38161ee56fa3f", null ],
      [ "certBlockSize", "a00040.html#aa3431f6aa34151afc142dda89afe81b1", null ]
    ] ],
    [ "nboot_ctrk_hash_table_t", "a00040.html#a00383", null ],
    [ "nboot_ecdsa_public_key_t", "a00040.html#a00384", [
      [ "x", "a00040.html#afc57c454bf498e2268647e5fd70234ab", null ],
      [ "y", "a00040.html#a69fe934095ec64f19b3eaaf69744defb", null ]
    ] ],
    [ "nboot_root_certificate_block_t", "a00040.html#a00389", [
      [ "flags", "a00040.html#a880c07edfaf8355a84ed6192df50eb13", null ],
      [ "ctrkHashTable", "a00040.html#a2798520f8a66e3f42e56d98dc00fd93b", null ],
      [ "rootPublicKey", "a00040.html#a80e2c36e5e4c17b5bba47ea6af8e91c5", null ]
    ] ],
    [ "nboot_ecdsa_signature_t", "a00040.html#a00385", [
      [ "r", "a00040.html#a242e72b01e7644d0a161beb603673d6a", null ],
      [ "s", "a00040.html#a1f9bf4043ee3f16645296fbe2607b5d0", null ]
    ] ],
    [ "nboot_isk_block_t", "a00040.html#a00388", [
      [ "signatureOffset", "a00040.html#a27239670b78549fc128dfb57778ad7ae", null ],
      [ "constraints", "a00040.html#ab1b63c338ecdb6abb772b286f3cc27ac", null ],
      [ "iskFlags", "a00040.html#a16c93639757c01adf06bf09ea61aed4c", null ],
      [ "iskPubKey", "a00040.html#a944bc276d5707b3e4de7d2af50cbd9e4", null ],
      [ "userData", "a00040.html#afe8a422e78a6ffc763e0ad440bfdacf8", null ],
      [ "iskSign", "a00040.html#a81dd7ea04d3df0807bcf141ba27a9b75", null ]
    ] ],
    [ "nboot_certificate_block_t", "a00040.html#a00380", [
      [ "iskBlock", "a00040.html#a49dbfae7c9b5ddb90b9bf74c9d1849e7", null ]
    ] ],
    [ "NBOOT_UUID_SIZE_IN_WORD", "a00040.html#ga12674a25ec43885fb80ae39846ebeade", null ],
    [ "NBOOT_PUF_AC_SIZE_IN_BYTE", "a00040.html#gaf8ffd65cf667de3a1e502a98ee0292b6", null ],
    [ "NBOOT_PUF_KC_SIZE_IN_BYTE", "a00040.html#ga605705852906ad4c4179cf4e7363d1f3", null ],
    [ "NBOOT_KEY_STORE_SIZE_IN_BYTE", "a00040.html#ga63f0cf8e9284438cf34f38b701e96f49", null ],
    [ "NBOOT_ROOT_ROTKH_SIZE_IN_WORD", "a00040.html#ga5d7c360820b6c396e54b470b7b5a66e3", null ],
    [ "NBOOT_KEY_BLOB_SIZE_IN_BYTE_256", "a00040.html#ga25286a58bc85d971714962ef2d4f7957", null ],
    [ "NBOOT_DBG_AUTH_DBG_STATE_MASK", "a00040.html#ga34707588c213158528871f4ad0f5b80a", null ],
    [ "NBOOT_DBG_AUTH_DBG_STATE_SHIFT", "a00040.html#ga921a86d78a406adfdf291592cd530a8f", null ],
    [ "NBOOT_DBG_AUTH_DBG_STATE_ALL_DISABLED", "a00040.html#gaf849e04d6575d2ff40a01d2e92f904f1", null ],
    [ "NBOOT_DICE_CSR_SIZE_IN_WORD", "a00040.html#ga59f39ebbd9f95f1cf8a3cb49f89ea9f2", null ],
    [ "NBOOT_DICE_CSR_ADDRESS", "a00040.html#ga41bb5792fb3fcbe6b92149ce6ec396bb", null ],
    [ "NBOOT_IPED_IV_OFFSET", "a00040.html#ga231d575efe68685d8d0f948ffc0d5723", null ],
    [ "nboot_timestamp_t", "a00040.html#ga2c3ede5c5413840e2423cfc637483d77", null ],
    [ "nboot_ecc_coordinate_t", "a00040.html#ga8c3d2e252bb28d70aa266bf891f1644c", null ],
    [ "nboot_hash_algo_t", "a00040.html#gaa460823161d2da328af65eafdebb35ab", [
      [ "kHASH_Sha1", "a00040.html#ggaa460823161d2da328af65eafdebb35aba38bd384e1e717110e18a55baf6bb785e", null ],
      [ "kHASH_Sha256", "a00040.html#ggaa460823161d2da328af65eafdebb35aba37a5f78eb51a050f62323476c17f6600", null ],
      [ "kHASH_Sha512", "a00040.html#ggaa460823161d2da328af65eafdebb35abab3a6a56ac90022a5f2f0bd4351ba3db7", null ],
      [ "kHASH_Aes", "a00040.html#ggaa460823161d2da328af65eafdebb35aba6757c781caec7370209b05f5eb626aac", null ],
      [ "kHASH_AesIcb", "a00040.html#ggaa460823161d2da328af65eafdebb35abab6bf5955b89a546c2750195172513b2b", null ]
    ] ]
];