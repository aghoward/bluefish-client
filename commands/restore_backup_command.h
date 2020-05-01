#pragma once

#include "commands/command.h"
#include "api/api.h"
#include "api/file.h"
#include "api/master_block.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"
#include "support/failure_reason.h"

#include "either/either.h"

#include <vector>

namespace detail {
    struct BackupFileDTO {
        MasterBlock master_block;
        std::vector<File> files;
    };
}

class RestoreBackupCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;

        bool query_user_confidence() const;
        either<detail::BackupFileDTO, FailureReason> read_backup_file(const std::string& filename) const;
        either<Success, APIFailureReason> write_files(const std::vector<File>& files);

    public:
        RestoreBackupCommand(
            API& api,
            FailureReasonTranslator& frt)
            :
            _api(api),
            _failure_reason_translator(frt)
        {}

        bool matches(const Arguments& args) const override;
        void execute(const Arguments& args) override;
};
