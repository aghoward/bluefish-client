#include "commands/create_backup_command.h"
#include "api/file.h"
#include "support/arguments.h"
#include "support/askpass.h"
#include "support/failure_reason.h"

#include "either/either.h"

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>


bool CreateBackupCommand::matches(const Arguments& args) const
{
    using namespace std::string_literals;
    return args.backup_file != ""s;
}

void CreateBackupCommand::execute(const Arguments& args)
{
    MasterBlock master_block;
    std::vector<File> files;

    _challenge_verifier.verify()
        .foldFirst([&] (auto&& result) {
            auto& [mb, mp] = result;
            master_block = mb;
            return _api.list_files()
                .mapSecond([&] (const APIFailureReason& failure) -> FailureReason {
                    return _failure_reason_translator.translate(failure);
                });
            })
        .foldFirst([&] (const auto& file_list) -> either<std::string, FailureReason> {
            for (const auto& filename : file_list) {
                const auto failureReason = _api.read_file(filename)
                    .match([&] (const auto& file) -> std::optional<APIFailureReason> {
                            files.push_back(file);
                            return {};
                        },
                        [&] (const auto& failure) -> std::optional<APIFailureReason> {
                            return failure;
                        });
                if (failureReason)
                    return _failure_reason_translator.translate(failureReason.value());
            }

            return write_file(master_block, files, args.backup_file);
            })
        .match(
            [] (const auto& filename) -> void {
                std::cout << "Backup file created: \"" << filename << "\"" << std::endl;
            },
            [&] (const auto& failure_reason) -> void {
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });
}

either<std::string, FailureReason> CreateBackupCommand::write_file(
    const MasterBlock& master_block,
    const std::vector<File>& files,
    const std::string& filename) const {
    using namespace bf;
    std::ofstream fd(filename, std::ios::binary);

    if (!fd.is_open())
        return FailureReason::CannotOpenFileFromDisk;
    fd << master_block;
    fd << static_cast<uint16_t>(files.size());
    for (const auto& file : files)
        fd << file;
    fd.close();

    return std::string(filename);
}
