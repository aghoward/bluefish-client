#pragma once

#include "api/api.h"
#include "commands/command.h"
#include "commands/challenge_verifier.h"
#include "encryption/encryption.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"

class ChangePasswordCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        ChallengeVerifier& _challenge_verifier;
        Encrypter& _encrypter;

    public:
        ChangePasswordCommand(
            API& api,
            FailureReasonTranslator& frt,
            ChallengeVerifier& cv,
            Encrypter& enc)
            :
            _api(api),
            _failure_reason_translator(frt),
            _challenge_verifier(cv),
            _encrypter(enc)
        {}

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};
