#pragma once

#include "api/api.h"
#include "commands/command.h"
#include "commands/challenge_verifier.h"
#include "encryption/encryption.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"

class ReadFileCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Encrypter& _encrypter;
        Decrypter& _decrypter;
        ChallengeVerifier& _challenge_verifier;

        void decrypt_file(
            const File& file,
            std::string&& master_password,
            const MasterBlock& master_block);
    public:
        ReadFileCommand(
            API& api,
            FailureReasonTranslator& frt,
            Encrypter& enc,
            Decrypter& dec,
            ChallengeVerifier& cv)
            :
            _api(api),
            _failure_reason_translator(frt),
            _encrypter(enc),
            _decrypter(dec),
            _challenge_verifier(cv)
            {}

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};
