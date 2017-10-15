//**********************************************************************;
// Copyright (c) 2015, Intel Corporation
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.
//**********************************************************************;

#ifndef TSS2_SYS_API_MARSHAL_UNMARSHAL_H
#define TSS2_SYS_API_MARSHAL_UNMARSHAL_H

#include "sapi/tss2_mu.h"

/*
 * The MARSHAL_ADAPTER macro generates code that adapts the old Marshal_* API
 * to the new libmarshal replacements.
 */
#define MARSHAL_ADAPTER(type, inBuffPtr, maxCommandSize, nextData, src, rval) \
    do { \
        if (*rval != TSS2_RC_SUCCESS) \
            break; \
        *rval = Tss2_MU_##type##_Marshal (src, \
                                inBuffPtr, \
                                maxCommandSize, \
                                nextData); \
    } while (0)
/*
 * The UNMARSHAL_ADAPTER macro generates code that adapts the old Unmarshal_*
 * API to the new libmarshal replacements.
 */
#define UNMARSHAL_ADAPTER(type, outBuffPtr, maxResponseSize, nextData, dest, rval) \
    do { \
        if (*rval != TSS2_RC_SUCCESS) \
            break; \
        \
        *rval = Tss2_MU_##type##_Unmarshal (outBuffPtr, \
                                  maxResponseSize, \
                                  nextData, \
                                  dest); \
    } while (0)

/*
 * The MARSHAL_ADAPTER macro generates code that adapts the old Marshal_TPMU_*
 * API to the new libmarshal replacements.
 */
#define MARSHAL_TPMU_ADAPTER(type, inBuffPtr, maxCommandSize, nextData, src, selector, rval) \
    do { \
        if (*rval != TSS2_RC_SUCCESS) \
            break; \
        *rval = Tss2_MU_##type##_Marshal (src, \
                                selector, \
                                inBuffPtr, \
                                maxCommandSize, \
                                nexData); \
    } while (0)
/*
 * The UNMARSHAL_ADAPTER macro generates code that adapts the old
 * Unmarshal_TPMU_* API to the new libmarshal replacements.
 */
#define UNMARSHAL_TPMU_ADAPTER(type, outBuffPtr, maxResponseSize, nextData, selector, dest, rval) \
    do { \
        if (*rval != TSS2_RC_SUCCESS) \
            break; \
        *rval = Tss2_MU_##type##_Unmarshal (outBuffPtr, \
                                  maxResponseSize, \
                                  nextData, \
                                  selector, \
                                  dest); \
    } while (0)


void Marshal_Simple_TPM2B(UINT8 *inBuffPtr, UINT32 maxCommandSize, size_t *nextData, TPM2B *value, TSS2_RC *rval);
void Unmarshal_Simple_TPM2B(UINT8 *outBuffPtr, UINT32 maxResponseSize, size_t *nextData, TPM2B *value, TSS2_RC *rval);
void Unmarshal_Simple_TPM2B_NoSizeCheck(UINT8 *outBuffPtr, UINT32 maxResponseSize, size_t *nextData, TPM2B *value, TSS2_RC *rval);
/*
 * These macros expand to adapter macros. They're meant to be a layer
 * adapting the existing Marshal_* API to the new stuff going into
 * libmarshal. The type being marshalled is the first parameter to the
 * MARSHAL_ADAPTER macro.
 * - inBuffPtr (UINT8*): Pointer to the beginning of the buffer where the
 *     response buffer resides.
 * - maxCommandSize (size_t): the size of the memory region pointed to by
 *     inBuffPtr.
 * - nextData (UINT8**): Pointer to the location in buffer referenced by
 *     inBuffPtr where then next value will be marshalled to.
 * - src (type): The instance of the type being marshalled.
 * - rval (TSS2_RC*): Pointer to TSS2_RC instace where the response code
 *     is stored.
 */
#define Marshal_TPM_ST(inBuffPtr, maxCommandSize, nextData, src, rval) \
    MARSHAL_ADAPTER(TPM_ST, inBuffPtr, maxCommandSize, nextData, src, rval)
#define Marshal_UINT64(inBuffPtr, maxCommandSize, nextData, src, rval) \
    MARSHAL_ADAPTER(UINT64, inBuffPtr, maxCommandSize, nextData, src, rval)
#define Marshal_UINT32(inBuffPtr, maxCommandSize, nextData, src, rval) \
    MARSHAL_ADAPTER(UINT32, inBuffPtr, maxCommandSize, nextData, src, rval)
#define Marshal_UINT16(inBuffPtr, maxCommandSize, nextData, src, rval) \
    MARSHAL_ADAPTER(UINT16, inBuffPtr, maxCommandSize, nextData, src, rval)
#define Marshal_UINT8(inBuffPtr, maxCommandSize, nextData, src, rval) \
    MARSHAL_ADAPTER(UINT8, inBuffPtr, maxCommandSize, nextData, src, rval)

#define Marshal_TPMA_ALGORITHM(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMA_ALGORITHM, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMA_CC(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMA_CC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMA_LOCALITY(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMA_LOCALITY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMA_NV(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMA_NV, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMA_OBJECT(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMA_OBJECT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMA_PERMANENT(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMA_PERMANENT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMA_SESSION(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMA_SESSION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMA_STARTUP_CLEAR(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMA_STARTUP_CLEAR, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPM2B_DIGEST(SYS_CONTEXT, digest) \
    MARSHAL_ADAPTER(TPM2B_DIGEST, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPM2B_ECC_POINT(SYS_CONTEXT, digest) \
    MARSHAL_ADAPTER(TPM2B_ECC_POINT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPM2B_NV_PUBLIC(SYS_CONTEXT, digest) \
    MARSHAL_ADAPTER(TPM2B_NV_PUBLIC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPM2B_SENSITIVE(SYS_CONTEXT, digest) \
    MARSHAL_ADAPTER(TPM2B_SENSITIVE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPM2B_SENSITIVE_CREATE(SYS_CONTEXT, digest) \
    MARSHAL_ADAPTER(TPM2B_SENSITIVE_CREATE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPM2B_CREATION_DATA(SYS_CONTEXT, digest) \
    MARSHAL_ADAPTER(TPM2B_CREATION_DATA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPM2B_PUBLIC(SYS_CONTEXT, digest) \
    MARSHAL_ADAPTER(TPM2B_PUBLIC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_ALGORITHM_DESCRIPTION(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_ALGORITHM_DESCRIPTION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_ALG_PROPERTY(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_ALG_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_AUTH_RESPONSE(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_AUTH_RESPONSE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_CERTIFY_INFO(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_CERTIFY_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_CLOCK_INFO(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_CLOCK_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_ALGORITHM_DESCRIPTION(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_ALGORITHM_DESCRIPTION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_CONTEXT(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_CONTEXT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_CONTEXT_DATA(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_CONTEXT_DATA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_CREATION_INFO(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_CREATION_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_ECC_POINT(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_ECC_POINT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_NV_CERTIFY_INFO(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_NV_CERTIFY_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_NV_PUBLIC(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_NV_PUBLIC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_SCHEME_ECDAA(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_SCHEME_ECDAA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_SCHEME_HASH(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_SCHEME_HASH, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_SCHEME_XOR(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_SCHEME_XOR, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_SESSION_AUDIT_INFO(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_SESSION_AUDIT_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_SIGNATURE_ECC(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_SIGNATURE_ECC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_SIGNATURE_RSA(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_SIGNATURE_RSA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_TAGGED_PROPERTY(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_TAGGED_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_TIME_ATTEST_INFO(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_TIME_ATTEST_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_TIME_INFO(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_TIME_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_SENSITIVE_CREATE(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_SENSITIVE_CREATE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_PCR_SELECT(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_PCR_SELECT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_PCR_SELECTION(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_PCR_SELECTION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_TAGGED_PCR_SELECT(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_TAGGED_PCR_SELECT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_QUOTE_INFO(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_QUOTE_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_CREATION_DATA(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_CREATION_DATA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_ECC_PARMS(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_ECC_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_ATTEST(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_ATTEST, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_ALGORITHM_DETAIL_ECC(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_ALGORITHM_DETAIL_ECC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_CAPABILITY_DATA(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_CAPABILITY_DATA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_KEYEDHASH_PARMS(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_KEYEDHASH_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_RSA_PARMS(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_RSA_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMS_SYMCIPHER_PARMS(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMS_SYMCIPHER_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_CC(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_CC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_CCA(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_CCA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_ALG(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_ALG, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_ALG_PROPERTY(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_ALG_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_HANDLE(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_HANDLE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_DIGEST(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_DIGEST, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_ECC_CURVE(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_ECC_CURVE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_TAGGED_TPM_PROPERTY(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_TAGGED_TPM_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_TAGGED_PCR_PROPERTY(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_TAGGED_PCR_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_PCR_SELECTION(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_PCR_SELECTION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPML_DIGEST_VALUES(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPML_DIGEST_VALUES, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_HA(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_HA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_CAPABILITIES(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_CAPABILITIES, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_ATTEST(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_ATTEST, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_SYM_MODE(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_SYM_MODE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_SYM_KEY_BITS(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_SYM_KEY_BITS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_SIG_SCHEME(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_SIG_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_KDF_SCHEME(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_KDF_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_ASYM_SCHEME(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_ASYM_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_SCHEME_KEYEDHASH(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_SCHEME_KEYEDHASH, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_SIGNATURE(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_SIGNATURE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_SENSITIVE_COMPOSITE(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_SENSITIVE_COMPOSITE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_PUBLIC_PARMS(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_PUBLIC_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMU_PUBLIC_ID(SYS_CONTEXT, var, sel) \
    MARSHAL_TPMU_ADAPTER(TPMU_PUBLIC_ID, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, sel, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_HA(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_HA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_SYM_DEF(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_SYM_DEF, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_SYM_DEF_OBJECT(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_SYM_DEF_OBJECT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_KEYEDHASH_SCHEME(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_KEYEDHASH_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_SIG_SCHEME(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_SIG_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_KDF_SCHEME(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_KDF_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_ASYM_SCHEME(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_ASYM_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_RSA_SCHEME(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_RSA_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_RSA_DECRYPT(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_RSA_DECRYPT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_ECC_SCHEME(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_ECC_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_SIGNATURE(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_SIGNATURE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_SENSITIVE(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_SENSITIVE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_TK_CREATION(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_TK_CREATION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_TK_VERIFIED(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_TK_VERIFIED, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_TK_AUTH(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_TK_AUTH, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_TK_HASHCHECK(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_TK_HASHCHECK, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_PUBLIC_PARMS(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_PUBLIC_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Marshal_TPMT_PUBLIC(SYS_CONTEXT, var) \
    MARSHAL_ADAPTER(TPMT_PUBLIC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

/*
 * These macros expand to adapter macros. They're meant to be a layer
 * adapting the existing Unmarshal_* API to the new stuff going into
 * libmarshal. The type being unmarshalled is the first parameter to the
 * UNMARSHAL_ADAPTER macro.
 * - outBuffPtr (UINT8*): Pointer to the beginning of the buffer where the
 *     response buffer resides.
 * - maxResponseSize (size_t): the size of the memory region pointed to by
 *     outBuffPtr.
 * - nextData (UINT8**): Pointer to the location in buffer referenced by
 *     outBuffPtr where then next value will be unmarshalled from.
 * - dest (type*): Pointer to an instance of the type being unmarshalled
 *     where the unmarshalled data will be stored.
 * - rval (TSS2_RC*): Pointer to TSS2_RC instace where the response code
 *     is stored
 */
#define Unmarshal_TPM_ST(outBuffPtr, maxResponseSize, nextData, dest, rval) \
    UNMARSHAL_ADAPTER(TPM_ST, outBuffPtr, maxResponseSize, nextData, dest, rval)
#define Unmarshal_UINT64(outBuffPtr, maxResponseSize, nextData, dest, rval) \
    UNMARSHAL_ADAPTER(UINT64, outBuffPtr, maxResponseSize, nextData, dest, rval)
#define Unmarshal_UINT32(outBuffPtr, maxResponseSize, nextData, dest, rval) \
    UNMARSHAL_ADAPTER(UINT32, outBuffPtr, maxResponseSize, nextData, dest, rval)
#define Unmarshal_UINT16(outBuffPtr, maxResponseSize, nextData, dest, rval) \
    UNMARSHAL_ADAPTER(UINT16, outBuffPtr, maxResponseSize, nextData, dest, rval)
#define Unmarshal_UINT8(outBuffPtr, maxResponseSize, nextData, dest, rval) \
    UNMARSHAL_ADAPTER(UINT8, outBuffPtr, maxResponseSize, nextData, dest, rval)

#define Unmarshal_TPMA_ALGORITHM(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMA_ALGORITHM, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMA_CC(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMA_CC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMA_LOCALITY(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMA_LOCALITY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMA_NV(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMA_NV, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMA_OBJECT(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMA_OBJECT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMA_PERMANENT(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMA_PERMANENT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMA_SESSION(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMA_SESSION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMA_STARTUP_CLEAR(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMA_STARTUP_CLEAR, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPM2B_DIGEST(SYS_CONTEXT, digest) \
    UNMARSHAL_ADAPTER(TPM2B_DIGEST, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPM2B_ECC_POINT(SYS_CONTEXT, digest) \
    UNMARSHAL_ADAPTER(TPM2B_ECC_POINT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPM2B_NV_PUBLIC(SYS_CONTEXT, digest) \
    UNMARSHAL_ADAPTER(TPM2B_NV_PUBLIC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPM2B_SENSITIVE(SYS_CONTEXT, digest) \
    UNMARSHAL_ADAPTER(TPM2B_SENSITIVE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPM2B_SENSITIVE_CREATE(SYS_CONTEXT, digest) \
    UNMARSHAL_ADAPTER(TPM2B_SENSITIVE_CREATE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPM2B_CREATION_DATA(SYS_CONTEXT, digest) \
    UNMARSHAL_ADAPTER(TPM2B_CREATION_DATA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPM2B_PUBLIC(SYS_CONTEXT, digest) \
    UNMARSHAL_ADAPTER(TPM2B_PUBLIC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            digest, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_ALGORITHM_DESCRIPTION(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_ALGORITHM_DESCRIPTION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_ALG_PROPERTY(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_ALG_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_AUTH_RESPONSE(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_AUTH_RESPONSE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_CERTIFY_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_CERTIFY_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_CLOCK_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_CLOCK_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_COMMAND_AUDIT_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_COMMAND_AUDIT_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_CONTEXT(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_CONTEXT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_CONTEXT_DATA(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_CONTEXT_DATA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_CREATION_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_CREATION_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_ECC_POINT(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_ECC_POINT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_NV_CERTIFY_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_NV_CERTIFY_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_NV_PUBLIC(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_NV_PUBLIC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_SCHEME_ECDAA(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_SCHEME_ECDAA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_SCHEME_HASH(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_SCHEME_HASH, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_SCHEME_XOR(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_SCHEME_XOR, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_SESSION_AUDIT_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_SESSION_AUDIT_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_SIGNATURE_ECC(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_SIGNATURE_ECC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_SIGNATURE_RSA(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_SIGNATURE_RSA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_TAGGED_PROPERTY(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_TAGGED_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_TIME_ATTEST_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_TIME_ATTEST_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_TIME_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_TIME_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_SENSITIVE_CREATE(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_SENSITIVE_CREATE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_PCR_SELECT(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_PCR_SELECT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_PCR_SELECTION(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_PCR_SELECTION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_TAGGED_PCR_SELECT(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_TAGGED_PCR_SELECT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_QUOTE_INFO(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_QUOTE_INFO, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_ECC_PARMS(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_ECC_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_ATTEST(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_ATTEST, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_ALGORITHM_DETAIL_ECC(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_ALGORITHM_DETAIL_ECC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_CAPABILITY_DATA(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_CAPABILITY_DATA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_KEYEDHASH_PARMS(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_KEYEDHASH_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_RSA_PARMS(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_RSA_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMS_SYMCIPHER_PARMS(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMS_SYMCIPHER_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_CC(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_CC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_CCA(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_CCA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_ALG(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_ALG, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_ALG_PROPERTY(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_ALG_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_HANDLE(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_HANDLE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_DIGEST(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_DIGEST, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_ECC_CURVE(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_ECC_CURVE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_TAGGED_TPM_PROPERTY(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_TAGGED_TPM_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_TAGGED_PCR_PROPERTY(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_TAGGED_PCR_PROPERTY, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_PCR_SELECTION(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_PCR_SELECTION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPML_DIGEST_VALUES(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPML_DIGEST_VALUES, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_HA(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_HA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_CAPABILITIES(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_CAPABILITIES, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_ATTEST(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_ATTEST, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_SYM_MODE(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_SYM_MODE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_SYM_KEY_BITS(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_SYM_KEY_BITS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_SIG_SCHEME(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_SIG_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_KDF_SCHEME(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_KDF_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_ASYM_SCHEME(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_ASYM_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_SCHEME_KEYEDHASH(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_SCHEME_KEYEDHASH, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_SIGNATURE(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_SIGNATURE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_SENSITIVE_COMPOSITE(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_SENSITIVE_COMPOSITE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_PUBLIC_PARMS(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_PUBLIC_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMU_PUBLIC_ID(SYS_CONTEXT, var, sel) \
    UNMARSHAL_TPMU_ADAPTER(TPMU_PUBLIC_ID, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            sel, var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_HA(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_HA, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_SYM_DEF(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_SYM_DEF, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_SYM_DEF_OBJECT(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_SYM_DEF_OBJECT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_KEYEDHASH_SCHEME(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_KEYEDHASH_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_SIG_SCHEME(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_SIG_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_KDF_SCHEME(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_KDF_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_ASYM_SCHEME(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_ASYM_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_RSA_SCHEME(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_RSA_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_RSA_DECRYPT(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_RSA_DECRYPT, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_ECC_SCHEME(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_ECC_SCHEME, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_SIGNATURE(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_SIGNATURE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_SENSITIVE(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_SENSITIVE, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_TK_CREATION(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_TK_CREATION, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_TK_VERIFIED(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_TK_VERIFIED, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_TK_AUTH(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_TK_AUTH, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_TK_HASHCHECK(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_TK_HASHCHECK, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_PUBLIC_PARMS(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_PUBLIC_PARMS, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

#define Unmarshal_TPMT_PUBLIC(SYS_CONTEXT, var) \
    UNMARSHAL_ADAPTER(TPMT_PUBLIC, ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->tpmInBuffPtr, \
            ((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->maxCommandSize, \
            &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->nextData), \
            var, &(((_TSS2_SYS_CONTEXT_BLOB *)SYS_CONTEXT)->rval))

// Macro for unmarshalling/marshalling in SYSAPI code.  We needed access to generic base functions in resource manager and
// other places
#define UNMARSHAL_SIMPLE_TPM2B( sysContext, value ) \
    Unmarshal_Simple_TPM2B( SYS_CONTEXT->tpmOutBuffPtr, SYS_CONTEXT->maxResponseSize, &( SYS_CONTEXT->nextData ), value, &(SYS_CONTEXT->rval ) )

#define UNMARSHAL_SIMPLE_TPM2B_NO_SIZE_CHECK( sysContext, value ) \
    Unmarshal_Simple_TPM2B_NoSizeCheck( SYS_CONTEXT->tpmOutBuffPtr, SYS_CONTEXT->maxResponseSize, &( SYS_CONTEXT->nextData ), value, &(SYS_CONTEXT->rval ) )

#define UNMARSHAL_TPMS_CONTEXT( sysContext, value ) \
    Unmarshal_TPMS_CONTEXT( SYS_CONTEXT->tpmOutBuffPtr, SYS_CONTEXT->maxResponseSize, &( SYS_CONTEXT->nextData ), value, &(SYS_CONTEXT->rval ) )

#define MARSHAL_SIMPLE_TPM2B( sysContext, value ) \
    Marshal_Simple_TPM2B( SYS_CONTEXT->tpmInBuffPtr, SYS_CONTEXT->maxCommandSize, &( SYS_CONTEXT->nextData ), value, &(SYS_CONTEXT->rval ) )

#define Marshal_TPM_ALGORITHM_ID( sysContext, var ) Marshal_UINT32( sysContext, (UINT32 *)var )

#define Unmarshal_TPM_ALGORITHM_ID( sysContext, var ) Unmarshal_UINT32( sysContext, (UINT32 *)var )

#define Marshal_TPM_MODIFIER_INDICATOR( sysContext, var ) Marshal_UINT32( sysContext, (UINT32 *)var )

#define Unmarshal_TPM_MODIFIER_INDICATOR( sysContext, var ) Unmarshal_UINT32( sysContext, (UINT32 *)var )

#define Marshal_TPM_AUTHORIZATION_SIZE( sysContext, var ) Marshal_UINT32( sysContext, (UINT32 *)var )

#define Unmarshal_TPM_AUTHORIZATION_SIZE( sysContext, var ) Unmarshal_UINT32( sysContext, (UINT32 *)var )

#define Marshal_TPM_PARAMETER_SIZE( sysContext, var ) Marshal_UINT32( sysContext, (UINT32 *)var )

#define Unmarshal_TPM_PARAMETER_SIZE( sysContext, var ) Unmarshal_UINT32( sysContext, (UINT32 *)var )

#define Marshal_TPM_KEY_SIZE( sysContext, var ) Marshal_UINT16( sysContext, (UINT16 *)var )

#define Unmarshal_TPM_KEY_SIZE( sysContext, var ) Unmarshal_UINT16( sysContext, (UINT16 *)var )

#define Marshal_TPM_KEY_BITS( sysContext, var ) Marshal_UINT16( sysContext, (UINT16 *)var )

#define Unmarshal_TPM_KEY_BITS( sysContext, var ) Unmarshal_UINT16( sysContext, (UINT16 *)var )

#define Marshal_TPM2B_NONCE( sysContext, var ) Marshal_TPM2B_DIGEST( sysContext, (TPM2B_DIGEST *)var )

#define Unmarshal_TPM2B_NONCE( sysContext, var ) Unmarshal_TPM2B_DIGEST( sysContext, (TPM2B_DIGEST *)var )

#define Marshal_TPM2B_AUTH( sysContext, var ) Marshal_TPM2B_DIGEST( sysContext, (TPM2B_DIGEST *)var )

#define Unmarshal_TPM2B_AUTH( sysContext, var ) Unmarshal_TPM2B_DIGEST( sysContext, (TPM2B_DIGEST *)var )

#define Marshal_TPM2B_OPERAND( sysContext, var ) Marshal_TPM2B_DIGEST( sysContext, (TPM2B_DIGEST *)var )

#define Unmarshal_TPM2B_OPERAND( sysContext, var ) Unmarshal_TPM2B_DIGEST( sysContext, (TPM2B_DIGEST *)var )

#define Marshal_TPM2B_TIMEOUT( sysContext, var ) Marshal_TPM2B_DIGEST( sysContext, (TPM2B_DIGEST *)var )

#define Unmarshal_TPM2B_TIMEOUT( sysContext, var ) Unmarshal_TPM2B_DIGEST( sysContext, (TPM2B_DIGEST *)var )

#define Marshal_TPMS_SCHEME_HMAC( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SCHEME_HMAC( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SIG_SCHEME_RSASSA( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SIG_SCHEME_RSASSA( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SIG_SCHEME_RSAPSS( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SIG_SCHEME_RSAPSS( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SIG_SCHEME_ECDSA( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SIG_SCHEME_ECDSA( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SIG_SCHEME_SM2( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SIG_SCHEME_SM2( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SIG_SCHEME_ECSCHNORR( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SIG_SCHEME_ECSCHNORR( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SIG_SCHEME_ECDAA( sysContext, var ) Marshal_TPMS_SCHEME_ECDAA( sysContext, (TPMS_SCHEME_ECDAA *)var )

#define Unmarshal_TPMS_SIG_SCHEME_ECDAA( sysContext, var ) Unmarshal_TPMS_SCHEME_ECDAA( sysContext, (TPMS_SCHEME_ECDAA *)var )

#define Marshal_TPMS_ENC_SCHEME_OAEP( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_ENC_SCHEME_OAEP( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_KEY_SCHEME_ECDH( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_KEY_SCHEME_ECDH( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_KEY_SCHEME_ECMQV( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_KEY_SCHEME_ECMQV( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SCHEME_MGF1( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SCHEME_MGF1( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SCHEME_KDF1_SP800_56A( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SCHEME_KDF1_SP800_56A( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SCHEME_KDF2( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SCHEME_KDF2( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SCHEME_KDF1_SP800_108( sysContext, var ) Marshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Unmarshal_TPMS_SCHEME_KDF1_SP800_108( sysContext, var ) Unmarshal_TPMS_SCHEME_HASH( sysContext, (TPMS_SCHEME_HASH *)var )

#define Marshal_TPMS_SIGNATURE_RSASSA( sysContext, var ) Marshal_TPMS_SIGNATURE_RSA( sysContext, (TPMS_SIGNATURE_RSA *)var )

#define Unmarshal_TPMS_SIGNATURE_RSASSA( sysContext, var ) Unmarshal_TPMS_SIGNATURE_RSA( sysContext, (TPMS_SIGNATURE_RSA *)var )

#define Marshal_TPMS_SIGNATURE_RSAPSS( sysContext, var ) Marshal_TPMS_SIGNATURE_RSA( sysContext, (TPMS_SIGNATURE_RSA *)var )

#define Unmarshal_TPMS_SIGNATURE_RSAPSS( sysContext, var ) Unmarshal_TPMS_SIGNATURE_RSA( sysContext, (TPMS_SIGNATURE_RSA *)var )

#define Marshal_TPMS_SIGNATURE_ECDSA( sysContext, var ) Marshal_TPMS_SIGNATURE_ECC( sysContext, (TPMS_SIGNATURE_ECC *)var )

#define Unmarshal_TPMS_SIGNATURE_ECDSA( sysContext, var ) Unmarshal_TPMS_SIGNATURE_ECC( sysContext, (TPMS_SIGNATURE_ECC *)var )

#define Marshal_TPMS_SIGNATURE_ECDAA( sysContext, var ) Marshal_TPMS_SIGNATURE_ECC( sysContext, (TPMS_SIGNATURE_ECC *)var )

#define Unmarshal_TPMS_SIGNATURE_ECDAA( sysContext, var ) Unmarshal_TPMS_SIGNATURE_ECC( sysContext, (TPMS_SIGNATURE_ECC *)var )

#define Marshal_TPMS_SIGNATURE_SM2( sysContext, var ) Marshal_TPMS_SIGNATURE_ECC( sysContext, (TPMS_SIGNATURE_ECC *)var )

#define Unmarshal_TPMS_SIGNATURE_SM2( sysContext, var ) Unmarshal_TPMS_SIGNATURE_ECC( sysContext, (TPMS_SIGNATURE_ECC *)var )

#define Marshal_TPMS_SIGNATURE_ECSCHNORR( sysContext, var ) Marshal_TPMS_SIGNATURE_ECC( sysContext, (TPMS_SIGNATURE_ECC *)var )

#define Unmarshal_TPMS_SIGNATURE_ECSCHNORR( sysContext, var ) Unmarshal_TPMS_SIGNATURE_ECC( sysContext, (TPMS_SIGNATURE_ECC *)var )

#endif
