/** @file
 * Copyright (c) 2019-2022, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/

#include "val_interfaces.h"
#include "val_target.h"
#include "test_c050.h"
#include "test_data.h"

const client_test_t test_c050_crypto_list[] = {
    NULL,
    psa_sign_message_test,
    psa_sign_message_negative_test,
    NULL,
};

extern  uint32_t g_test_count;
static int32_t  valid_test_input_index = -1;


int32_t psa_sign_message_test(caller_security_t caller __UNUSED)
{
#if (defined(ARCH_TEST_RSA_1024) ||\
(defined(ARCH_TEST_SHA256) && (defined(ARCH_TEST_DETERMINISTIC_ECDSA) || defined(ARCH_TEST_ECC_CURVE_SECP256R1)))) // NXP
    int32_t                 num_checks = sizeof(check1)/sizeof(check1[0]);
    int32_t                 i, status;
    size_t                  get_signature_length;
    psa_key_attributes_t    attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_id_t            key;

    if (num_checks == 0)
    {
        val->print(PRINT_TEST, "No test available for the selected crypto configuration\n", 0);
        return RESULT_SKIP(VAL_STATUS_NO_TESTS);
    }

    /* Initialize the PSA crypto library*/
    status = val->crypto_function(VAL_CRYPTO_INIT);
    TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(1));

    for (i = 0; i < num_checks; i++)
    {
        val->print(PRINT_TEST, "[Check %d] ", g_test_count++);
        val->print(PRINT_TEST, check1[i].test_desc, 0);

        /* Setting up the watchdog timer for each check */
        status = val->wd_reprogram_timer(WD_CRYPTO_TIMEOUT);
        TEST_ASSERT_EQUAL(status, VAL_STATUS_SUCCESS, TEST_CHECKPOINT_NUM(2));

        /* Setup the attributes for the key */
        val->crypto_function(VAL_CRYPTO_SET_KEY_TYPE,
                             &attributes,
                             check1[i].type);
        val->crypto_function(VAL_CRYPTO_SET_KEY_ALGORITHM,
                             &attributes,
                             check1[i].alg);
        val->crypto_function(VAL_CRYPTO_SET_KEY_USAGE_FLAGS,
                             &attributes,
                             check1[i].usage_flags);

        /* Import the key data into the key slot */
        status = val->crypto_function(VAL_CRYPTO_IMPORT_KEY,
                                      &attributes,
                                      check1[i].data,
                                      check1[i].data_length,
                                      &key);
        TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(3));

        /* Sign a message with a private key */
        status = val->crypto_function(VAL_CRYPTO_SIGN_MESSAGE,
                                      key,
                                      check1[i].sign_alg,
                                      check1[i].input,
                                      check1[i].input_length,
                                      check1[i].signature,
                                      check1[i].signature_size,
                                      &get_signature_length);
        TEST_ASSERT_EQUAL(status, check1[i].expected_status, TEST_CHECKPOINT_NUM(4));

        if (check1[i].expected_status != PSA_SUCCESS)
        {
            /* Destroy the key */
            status = val->crypto_function(VAL_CRYPTO_DESTROY_KEY,
                                          key);
            TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(5));

            continue;
        }

        /* Check if the output length matches with the expected length */
        TEST_ASSERT_EQUAL(get_signature_length, check1[i].expected_signature_length,
                          TEST_CHECKPOINT_NUM(6));

        /* Check if the output matches with the expected data */
        TEST_ASSERT_MEMCMP(check1[i].signature, check1[i].expected_signature, get_signature_length,
                           TEST_CHECKPOINT_NUM(7));

        /* Destroy the key */
        status = val->crypto_function(VAL_CRYPTO_DESTROY_KEY,
                                      key);
        TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(8));

        if (valid_test_input_index < 0)
            valid_test_input_index = i;
    }

    return VAL_STATUS_SUCCESS;
#else //NXP
    val->print(PRINT_TEST, "No test available for the selected crypto configuration\n", 0);
    return RESULT_SKIP(VAL_STATUS_NO_TESTS);
#endif //NXP
}

int32_t psa_sign_message_negative_test(caller_security_t caller __UNUSED)
{
#if (defined(ARCH_TEST_RSA_1024) ||\
(defined(ARCH_TEST_SHA256) && (defined(ARCH_TEST_DETERMINISTIC_ECDSA) || defined(ARCH_TEST_ECC_CURVE_SECP256R1)))) // NXP
    int32_t                 status;
    size_t                  get_signature_length;
    psa_key_id_t            key = 10;

    if (valid_test_input_index < 0)
        return RESULT_SKIP(VAL_STATUS_NO_TESTS);

    /* Initialize the PSA crypto library*/
    status = val->crypto_function(VAL_CRYPTO_INIT);
    TEST_ASSERT_EQUAL(status, PSA_SUCCESS, TEST_CHECKPOINT_NUM(1));

    /* Setting up the watchdog timer for each check */
    status = val->wd_reprogram_timer(WD_CRYPTO_TIMEOUT);
    TEST_ASSERT_EQUAL(status, VAL_STATUS_SUCCESS, TEST_CHECKPOINT_NUM(2));

    val->print(PRINT_TEST, "[Check %d] Test psa_sign_message - Invalid key handle\n",
                                                                            g_test_count++);
    /* Sign a message with a private key */
    status = val->crypto_function(VAL_CRYPTO_SIGN_MESSAGE,
                                  key,
                                  check1[valid_test_input_index].sign_alg,
                                  check1[valid_test_input_index].input,
                                  check1[valid_test_input_index].input_length,
                                  check1[valid_test_input_index].signature,
                                  check1[valid_test_input_index].signature_size,
                                  &get_signature_length);
    TEST_ASSERT_EQUAL(status, PSA_ERROR_INVALID_HANDLE, TEST_CHECKPOINT_NUM(3));

    val->print(PRINT_TEST, "[Check %d] Test psa_sign_message - Zero as key handle\n",
                                                                            g_test_count++);
    /* Sign message with a private key */
    status = val->crypto_function(VAL_CRYPTO_SIGN_MESSAGE,
                                  0,
                                  check1[valid_test_input_index].sign_alg,
                                  check1[valid_test_input_index].input,
                                  check1[valid_test_input_index].input_length,
                                  check1[valid_test_input_index].signature,
                                  check1[valid_test_input_index].signature_size,
                                  &get_signature_length);
    TEST_ASSERT_EQUAL(status, PSA_ERROR_INVALID_HANDLE, TEST_CHECKPOINT_NUM(4));

    return VAL_STATUS_SUCCESS;
#else //NXP
    val->print(PRINT_TEST, "No test available for the selected crypto configuration\n", 0);
    return RESULT_SKIP(VAL_STATUS_NO_TESTS);
#endif //NXP
}
