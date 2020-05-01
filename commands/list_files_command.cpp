#include "commands/list_files_command.h"

#include "api/api.h"
#include "api/master_block.h"
#include "encryption/encryption_helpers.h"
#include "support/arguments.h"
#include "support/askpass.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void ListFilesCommand::execute(const Arguments&)
{
    auto master_password = askpass("Master Password: ");
    _challenge_verifier.verify(std::string(master_password))
        .match(
            [&] (const auto& master_block) {
                _api.list_files()
                    .match(
                        [&] (auto&& encrypted_filenames) {
                            list_files(master_block, std::move(master_password), encrypted_filenames);
                        },
                        [&] (auto&& api_failure_reason) {
                            auto failure_reason = _failure_reason_translator.translate(api_failure_reason);
                            std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
                        });

            },
            [&] (const auto& failure) {
                std::cout << _failure_reason_translator.to_string(failure) << std::endl;
            });
}

bool ListFilesCommand::matches(const Arguments& arguments) const
{
    return arguments.list;
}

void ListFilesCommand::list_files(
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
    for (auto& filename : filenames)
        std::cout << filename << std::endl;
}
