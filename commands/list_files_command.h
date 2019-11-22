#pragma once

#include "api/api.h"
#include "commands/command.h"
#include "commands/challenge_verifier.h"
#include "encryption/encryption.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"

class ListFilesCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        ChallengeVerifier& _challenge_verifier;
        Decrypter& _decrypter;

        void list_files(
            const MasterBlock& master_block,
            std::string&& master_password,
            const std::vector<std::string>& encrypted_filenames);

    public:
        ListFilesCommand(API& api, FailureReasonTranslator& frt, ChallengeVerifier& cv, Decrypter& dec)
            :
            _api(api),
            _failure_reason_translator(frt),
            _challenge_verifier(cv),
            _decrypter(dec)
        {}
        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};
