/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include <setjmp.h>
#include <cmocka.h>

#include "tpm2_cc_util.h"
#include "tpm2_util.h"

static void test_tpm2_cc_util_from_str_null_str_ptr(void **state) {
    UNUSED(state);

    TPM2_CC cc;
    bool result = tpm2_cc_util_from_str(NULL, &cc);
    assert_false(result);
}

static void test_tpm2_cc_util_from_str_null_cc_ptr(void **state) {
    UNUSED(state);

    bool result = tpm2_cc_util_from_str("duplicate", NULL);
    assert_false(result);
}

static void test_tpm2_cc_util_from_str_null_ptrs(void **state) {
    UNUSED(state);

    bool result = tpm2_cc_util_from_str(NULL, NULL);
    assert_false(result);
}

static void test_tpm2_cc_util_from_str_invalid_str(void **state) {
    UNUSED(state);

    TPM2_CC cc = 0;
    bool result = tpm2_cc_util_from_str("nofound", &cc);
    assert_false(result);
    assert_int_equal(cc, 0);
}

static void test_tpm2_cc_util_from_str_empty_str(void **state) {
    UNUSED(state);

    TPM2_CC cc = 0;
    bool result = tpm2_cc_util_from_str("", &cc);
    assert_false(result);
    assert_int_equal(cc, 0);
}

static void test_tpm2_cc_util_from_str_valid_hex_str(void **state) {
    UNUSED(state);

    TPM2_CC cc = 0;
    bool result = tpm2_cc_util_from_str("0x42", &cc);
    assert_true(result);
    assert_int_equal(cc, 0x42);
}

typedef struct cc_map cc_map;
struct cc_map {
    TPM2_CC cc;
    const char *str;
};

#define ADDCC(s, c) { .str = s, .cc = c }

static void test_tpm2_cc_util_from_str_validate_map(void **state) {
    UNUSED(state);

    static const cc_map map[] = {
        ADDCC("nvundefinespacespecial", TPM2_CC_NV_UndefineSpaceSpecial),
        ADDCC("evictcontrol", TPM2_CC_EvictControl),
        ADDCC("hierarchycontrol", TPM2_CC_HierarchyControl),
        ADDCC("nvundefinespace", TPM2_CC_NV_UndefineSpace),
        ADDCC("changeeps", TPM2_CC_ChangeEPS),
        ADDCC("changepps", TPM2_CC_ChangePPS),
        ADDCC("clear", TPM2_CC_Clear),
        ADDCC("clearcontrol", TPM2_CC_ClearControl),
        ADDCC("clockset", TPM2_CC_ClockSet),
        ADDCC("hierarchychangeauth", TPM2_CC_HierarchyChangeAuth),
        ADDCC("nvdefinespace", TPM2_CC_NV_DefineSpace),
        ADDCC("pcrallocate", TPM2_CC_PCR_Allocate),
        ADDCC("pcrsetauthpolicy", TPM2_CC_PCR_SetAuthPolicy),
        ADDCC("ppcommands", TPM2_CC_PP_Commands),
        ADDCC("setprimarypolicy", TPM2_CC_SetPrimaryPolicy),
        ADDCC("fieldupgradestart", TPM2_CC_FieldUpgradeStart),
        ADDCC("clockrateadjust", TPM2_CC_ClockRateAdjust),
        ADDCC("createprimary", TPM2_CC_CreatePrimary),
        ADDCC("nvglobalwritelock", TPM2_CC_NV_GlobalWriteLock),
        ADDCC("getcommandauditdigest", TPM2_CC_GetCommandAuditDigest),
        ADDCC("nvincrement", TPM2_CC_NV_Increment),
        ADDCC("nvsetbits", TPM2_CC_NV_SetBits),
        ADDCC("nvextend", TPM2_CC_NV_Extend),
        ADDCC("nvwrite", TPM2_CC_NV_Write),
        ADDCC("nvwritelock", TPM2_CC_NV_WriteLock),
        ADDCC("dictionaryattacklockreset", TPM2_CC_DictionaryAttackLockReset),
        ADDCC("dictionaryattackparameters", TPM2_CC_DictionaryAttackParameters),
        ADDCC("nvchangeauth", TPM2_CC_NV_ChangeAuth),
        ADDCC("pcrevent", TPM2_CC_PCR_Event),
        ADDCC("pcrreset", TPM2_CC_PCR_Reset),
        ADDCC("sequencecomplete", TPM2_CC_SequenceComplete),
        ADDCC("setalgorithmset", TPM2_CC_SetAlgorithmSet),
        ADDCC("setcommandcodeauditstatus", TPM2_CC_SetCommandCodeAuditStatus),
        ADDCC("fieldupgradedata", TPM2_CC_FieldUpgradeData),
        ADDCC("incrementalselftest", TPM2_CC_IncrementalSelfTest),
        ADDCC("selftest", TPM2_CC_SelfTest),
        ADDCC("startup", TPM2_CC_Startup),
        ADDCC("shutdown", TPM2_CC_Shutdown),
        ADDCC("stirrandom", TPM2_CC_StirRandom),
        ADDCC("activatecredential", TPM2_CC_ActivateCredential),
        ADDCC("certify", TPM2_CC_Certify),
        ADDCC("policynv", TPM2_CC_PolicyNV),
        ADDCC("certifycreation", TPM2_CC_CertifyCreation),
        ADDCC("duplicate", TPM2_CC_Duplicate),
        ADDCC("gettime", TPM2_CC_GetTime),
        ADDCC("getsessionauditdigest", TPM2_CC_GetSessionAuditDigest),
        ADDCC("nvread", TPM2_CC_NV_Read),
        ADDCC("nvreadlock", TPM2_CC_NV_ReadLock),
        ADDCC("objectchangeauth", TPM2_CC_ObjectChangeAuth),
        ADDCC("policysecret", TPM2_CC_PolicySecret),
        ADDCC("rewrap", TPM2_CC_Rewrap),
        ADDCC("create", TPM2_CC_Create),
        ADDCC("ecdhzgen", TPM2_CC_ECDH_ZGen),
        ADDCC("hmac", TPM2_CC_HMAC),
        ADDCC("import", TPM2_CC_Import),
        ADDCC("load", TPM2_CC_Load),
        ADDCC("quote", TPM2_CC_Quote),
        ADDCC("rsadecrypt", TPM2_CC_RSA_Decrypt),
        ADDCC("hmacstart", TPM2_CC_HMAC_Start),
        ADDCC("sequenceupdate", TPM2_CC_SequenceUpdate),
        ADDCC("sign", TPM2_CC_Sign),
        ADDCC("unseal", TPM2_CC_Unseal),
        ADDCC("policysigned", TPM2_CC_PolicySigned),
        ADDCC("contextload", TPM2_CC_ContextLoad),
        ADDCC("contextsave", TPM2_CC_ContextSave),
        ADDCC("ecdhkeygen", TPM2_CC_ECDH_KeyGen),
        ADDCC("encryptdecrypt", TPM2_CC_EncryptDecrypt),
        ADDCC("flushcontext", TPM2_CC_FlushContext),
        ADDCC("loadexternal", TPM2_CC_LoadExternal),
        ADDCC("makecredential", TPM2_CC_MakeCredential),
        ADDCC("nvreadpublic", TPM2_CC_NV_ReadPublic),
        ADDCC("policyauthorize", TPM2_CC_PolicyAuthorize),
        ADDCC("policyauthvalue", TPM2_CC_PolicyAuthValue),
        ADDCC("policycommandcode", TPM2_CC_PolicyCommandCode),
        ADDCC("policycountertimer", TPM2_CC_PolicyCounterTimer),
        ADDCC("policycphash", TPM2_CC_PolicyCpHash),
        ADDCC("policylocality", TPM2_CC_PolicyLocality),
        ADDCC("policynamehash", TPM2_CC_PolicyNameHash),
        ADDCC("policyor", TPM2_CC_PolicyOR),
        ADDCC("policyticket", TPM2_CC_PolicyTicket),
        ADDCC("readpublic", TPM2_CC_ReadPublic),
        ADDCC("rsaencrypt", TPM2_CC_RSA_Encrypt),
        ADDCC("startauthsession", TPM2_CC_StartAuthSession),
        ADDCC("verifysignature", TPM2_CC_VerifySignature),
        ADDCC("eccparameters", TPM2_CC_ECC_Parameters),
        ADDCC("firmwareread", TPM2_CC_FirmwareRead),
        ADDCC("getcapability", TPM2_CC_GetCapability),
        ADDCC("getrandom", TPM2_CC_GetRandom),
        ADDCC("gettestresult", TPM2_CC_GetTestResult),
        ADDCC("hash", TPM2_CC_Hash),
        ADDCC("pcrread", TPM2_CC_PCR_Read),
        ADDCC("policypcr", TPM2_CC_PolicyPCR),
        ADDCC("policyrestart", TPM2_CC_PolicyRestart),
        ADDCC("readclock", TPM2_CC_ReadClock),
        ADDCC("pcrextend", TPM2_CC_PCR_Extend),
        ADDCC("pcrsetauthvalue", TPM2_CC_PCR_SetAuthValue),
        ADDCC("nvcertify", TPM2_CC_NV_Certify),
        ADDCC("eventsequencecomplete", TPM2_CC_EventSequenceComplete),
        ADDCC("hashsequencestart", TPM2_CC_HashSequenceStart),
        ADDCC("policyphysicalpresence", TPM2_CC_PolicyPhysicalPresence),
        ADDCC("policyduplicationselect", TPM2_CC_PolicyDuplicationSelect),
        ADDCC("policygetdigest", TPM2_CC_PolicyGetDigest),
        ADDCC("testparms", TPM2_CC_TestParms),
        ADDCC("commit", TPM2_CC_Commit),
        ADDCC("policypassword", TPM2_CC_PolicyPassword),
        ADDCC("zgen2phase", TPM2_CC_ZGen_2Phase),
        ADDCC("ecephemeral", TPM2_CC_EC_Ephemeral),
        ADDCC("policynvwritten", TPM2_CC_PolicyNvWritten),
        ADDCC("policytemplate", TPM2_CC_PolicyTemplate),
        ADDCC("createloaded", TPM2_CC_CreateLoaded),
        ADDCC("policyauthorizenv", TPM2_CC_PolicyAuthorizeNV),
        ADDCC("encryptdecrypt2", TPM2_CC_EncryptDecrypt2),
        ADDCC("acgetcapability", TPM2_CC_AC_GetCapability),
        ADDCC("acsend", TPM2_CC_AC_Send),
        ADDCC("policyacsendselect", TPM2_CC_Policy_AC_SendSelect),
        ADDCC("vendortcgtest", TPM2_CC_Vendor_TCG_Test),
    };

    size_t i;
    for (i = 0; i < ARRAY_LEN(map); i++) {
        const cc_map *m = &map[i];
        TPM2_CC expected = m->cc;
        TPM2_CC got = 0;
        bool result = tpm2_cc_util_from_str(m->str, &got);
        assert_true(result);
        assert_int_equal(got, expected);
    }
}

/* link required symbol, but tpm2_tool.c declares it AND main, which
 * we have a main below for cmocka tests.
 */
bool output_enabled = true;

int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_tpm2_cc_util_from_str_null_str_ptr),
        cmocka_unit_test(test_tpm2_cc_util_from_str_null_cc_ptr),
        cmocka_unit_test(test_tpm2_cc_util_from_str_null_ptrs),
        cmocka_unit_test(test_tpm2_cc_util_from_str_invalid_str),
        cmocka_unit_test(test_tpm2_cc_util_from_str_empty_str),
        cmocka_unit_test(test_tpm2_cc_util_from_str_valid_hex_str),
        cmocka_unit_test(test_tpm2_cc_util_from_str_validate_map),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
