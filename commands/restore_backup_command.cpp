#include "commands/restore_backup_command.h"

#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "api/file.h"
#include "api/master_block.h"
#include "commands/common/read_backup_file.h"
#include "commands/models/backup_file_dto.h"
#include "either/either.h"
#include "encryption/encryption_helpers.h"
#include "support/failure_reason.h"

either<bf::Success, APIFailureReason> RestoreBackupCommand::write_files(const std::vector<File>& files)
{
    for (const auto& file : files)
    {
        auto result = _api.write_file(file)
            .match(
                [] (const auto&) -> std::optional<APIFailureReason> { return {}; },
                [] (const auto& failure) -> std::optional<APIFailureReason> { return failure; });
        if (result)
            return result.value();
    }

    return bf::Success{};
}

either<bf::Success, RestoreBackupFailure> RestoreBackupCommand::execute(const std::string& backup_filename)
{
    return bf::read_backup_file(backup_filename)
        .foldFirst([&] (const auto& backup_data) {
            return _api.format(backup_data.master_block.encryption_iv, backup_data.master_block.challenge)
                .foldFirst([&] (auto&&) {
                    return write_files(backup_data.files);
                })
                .mapSecond([&] (const auto& failure) {
                    return RestoreBackupFailure(_failure_reason_translator.translate(failure));
                });
        });
}
