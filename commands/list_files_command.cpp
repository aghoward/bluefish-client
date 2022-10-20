#include "commands/list_files_command.h"

#include <algorithm>
#include <string>
#include <vector>

#include "api/api.h"
#include "api/master_block.h"
#include "encryption/encryption_helpers.h"

either<std::vector<std::string>, FailureReason> ListFilesCommand::execute(
        const MasterBlock& master_block,
        std::string&& master_password)
{
    return _api.list_files()
        .map(
            [&] (auto&& encrypted_filenames) {
                return list_files(master_block, std::move(master_password), encrypted_filenames);
            },
            [&] (auto&& api_failure_reason) {
                return _failure_reason_translator.translate(api_failure_reason);
            });
}

std::vector<std::string> ListFilesCommand::list_files(
        const MasterBlock& master_block,
        std::string&& master_password,
        const std::vector<std::string>& encrypted_filenames)
{
    using namespace std::string_literals;

    auto filenames = std::vector<std::string>(encrypted_filenames.size());
    std::transform(
        encrypted_filenames.begin(),
        encrypted_filenames.end(),
        filenames.begin(),
        [&] (auto&& encrypted) -> std::string {
            return _decrypter.decrypt(
                encrypted,
                std::string(master_password),
                master_block.encryption_iv)
            .match(
                [] (auto&& filename) { return filename; },
                [] (auto&&) { return ""s; });
        });
    clear_data(master_password);

    std::sort(
        filenames.begin(),
        filenames.end(),
        [] (const auto& first, const auto& second) {
            return first < second;
        });

    return filenames;
}
