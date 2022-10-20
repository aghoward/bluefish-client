#pragma once

#include <vector>

#include "api/api.h"
#include "api/file.h"
#include "either/either.h"
#include "support/failure_reason.h"
#include "support/failure_reason_translator.h"
#include "support/success.h"

class RestoreBackupCommand
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;

        either<bf::Success, APIFailureReason> write_files(const std::vector<File>& files);

    public:
        RestoreBackupCommand(
            API& api,
            FailureReasonTranslator& frt)
            :
            _api(api),
            _failure_reason_translator(frt)
        {}

        either<bf::Success, RestoreBackupFailure> execute(const std::string& backup_filename);
};
