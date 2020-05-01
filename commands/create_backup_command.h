#pragma once

#include "api/api.h"
#include "api/master_block.h"
#include "commands/command.h"
#include "commands/challenge_verifier.h"
#include "either/either.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"
#include "support/failure_reason.h"

#include <string>
#include <vector>

class CreateBackupCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        ChallengeVerifier& _challenge_verifier;

        either<std::string, FailureReason> write_file(
            const MasterBlock& mb,
            const std::vector<File>& files,
            const std::string& filename) const;
    public:
        CreateBackupCommand(
            API& api,
            FailureReasonTranslator& frt,
            ChallengeVerifier& cv)
            :
            _api(api),
            _failure_reason_translator(frt),
            _challenge_verifier(cv)
        {}

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};

