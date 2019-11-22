#pragma once

#include "api/api.h"
#include "commands/command.h"
#include "commands/challenge_verifier.h"
#include "encryption/encryption.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"

class AddFileCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Encrypter& _encrypter;
        ChallengeVerifier& _challenge_verifier;

        void write_file(
            const std::string& filename,
            const std::string& username,
            const std::string& password);
    public:
        AddFileCommand(
            API& api,
            FailureReasonTranslator& frt,
            Encrypter& enc,
            ChallengeVerifier& cv)
            :
            _api(api),
            _failure_reason_translator(frt),
            _encrypter(enc),
            _challenge_verifier(cv)
        {}

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};
