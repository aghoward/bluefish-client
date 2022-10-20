#pragma once

#include <tuple>

#include "api/api.h"
#include "api/master_block.h"
#include "either/either.h"
#include "encryption/encryption.h"
#include "support/failure_reason.h"
#include "support/success.h"

class VerifyChallengeCommand
{
    private:
        API& _api;
        Decrypter& _decrypter;

        either<bf::Success, ChallengeFailure> verify_entered_password(
                const MasterBlock& master_block,
                const std::string& password) const;
    public:
        VerifyChallengeCommand(API& api, Decrypter& dec)
            : _api(api), _decrypter(dec) {}

        either<MasterBlock, ChallengeFailure> verify(const std::string& password) const;
};
