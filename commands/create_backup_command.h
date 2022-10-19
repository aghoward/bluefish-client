#pragma once

#include <string>
#include <vector>

#include "api/api.h"
#include "api/master_block.h"
#include "either/either.h"
#include "support/failure_reason.h"
#include "support/failure_reason_translator.h"
#include "support/success.h"

class CreateBackupCommand
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;

        either<bf::Success, CreateBackupFailure> write_file(
                const MasterBlock& master_block,
                const std::vector<File>& files,
                const std::string& filename) const;
    public:
        CreateBackupCommand(
            API& api,
            FailureReasonTranslator& frt)
            :
            _api(api),
            _failure_reason_translator(frt)
        {}

        either<bf::Success, CreateBackupFailure> execute(
                const MasterBlock& master_block,
                const std::string& backup_filename);
};

