#include "commands/restore_backup_command.h"

#include "api/api.h"
#include "api/file.h"
#include "api/master_block.h"
#include "commands/common/read_backup_file.h"
#include "commands/models/backup_file_dto.h"
#include "support/arguments.h"
#include "support/failure_reason.h"
#include "encryption/encryption_helpers.h"

#include "either/either.h"

#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

bool RestoreBackupCommand::matches(const Arguments& args) const
{
    using namespace std::string_literals;
    return args.restore_file != ""s;
}

bool RestoreBackupCommand::query_user_confidence() const
{
    using namespace std::string_literals;

    auto response = std::string();
    std::cout << "Are you sure you want to erase your device and restore the backup file? (yes/no): " << std::endl;
    std::getline(std::cin, response);
    return response == "yes"s;
}

either<Success, APIFailureReason> RestoreBackupCommand::write_files(const std::vector<File>& files)
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

    return Success{};
}

void RestoreBackupCommand::execute(const Arguments& args)
{
    if (!query_user_confidence())
        return;

    BackupFileDTO data;

    bf::read_backup_file(args.restore_file)
        .foldFirst([&] (const auto& backup_data) {
            data = backup_data;
            return _api.format(data.master_block.encryption_iv, data.master_block.challenge)
                .mapSecond([&] (const auto& failure) {
                    return _failure_reason_translator.translate(failure);
                });
            })
        .foldFirst([&] (const auto&) {
            return write_files(data.files)
                .mapSecond([&] (const auto& failure) {
                    return _failure_reason_translator.translate(failure);
                });
            })
        .match(
            [] (const auto&) {
                std::cout << "Restore complete!" << std::endl;
            },
            [&] (const auto& failure) {
                std::cout << _failure_reason_translator.to_string(failure) << std::endl;
            });
}
