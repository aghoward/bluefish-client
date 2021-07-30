#pragma once

#include <tuple>

#include "encryption/encryption.h"
#include "api/api.h"
#include "api/master_block.h"
#include "either/either.h"
#include "support/failure_reason.h"
#include "support/failure_reason_translator.h"

class ChallengeVerifier
{
    private:
        API& _api;
        Decrypter& _decrypter;
        FailureReasonTranslator& _failure_reason_translator;

        either<std::string, FailureReason> verify_entered_password(const MasterBlock& master_block) const;
    public:
        ChallengeVerifier(API& api, Decrypter& dec, FailureReasonTranslator& frt)
            : _api(api), _decrypter(dec), _failure_reason_translator(frt) {}

        either<std::tuple<MasterBlock, std::string>, FailureReason> verify() const;
};
