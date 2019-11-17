#pragma once

#include "encryption/encryption.h"
#include "api/api.h"
#include "either/either.h"
#include "support/failure_reason.h"
#include "support/failure_reason_translator.h"

class ChallengeVerifier
{
    private:
        API& _api;
        Decrypter& _decrypter;
        FailureReasonTranslator& _failure_reason_translator;

    public:
        ChallengeVerifier(API& api, Decrypter& dec, FailureReasonTranslator& frt)
            : _api(api), _decrypter(dec), _failure_reason_translator(frt) {}

        either<MasterBlock, FailureReason> verify(std::string&& password);
};
