#include "commands/create_backup_command.h"

#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "api/file.h"
#include "either/either.h"
#include "support/failure_reason.h"
#include "support/success.h"

either<bf::Success, CreateBackupFailure> CreateBackupCommand::execute(
        const MasterBlock& master_block,
        const std::string& backup_filename)
{
    return _api.list_files()
        .mapSecond([&] (const APIFailureReason& failure) -> CreateBackupFailure {
            return CreateBackupFailure(failure);
        })
        .foldFirst([&] (const auto& file_list) -> either<bf::Success, CreateBackupFailure> {
            std::vector<File> files;
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
                    return CreateBackupFailure(_failure_reason_translator.translate(failureReason.value()));
            }

            return write_file(master_block, files, backup_filename);
        });
}

either<bf::Success, CreateBackupFailure> CreateBackupCommand::write_file(
        const MasterBlock& master_block,
        const std::vector<File>& files,
        const std::string& filename) const
{
    using namespace bf;
    std::ofstream fd(filename, std::ios::binary);

    if (!fd.is_open())
        return CreateBackupFailure::CannotOpenFileFromDisk;
    fd << master_block;
    fd << static_cast<uint16_t>(files.size());
    for (const auto& file : files)
        fd << file;
    fd.close();

    return bf::Success{};
}
