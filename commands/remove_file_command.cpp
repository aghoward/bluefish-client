#include "commands/remove_file_command.h"

#include "encryption/encryption_helpers.h"
#include "support/arguments.h"
#include "support/askpass.h"

#include <iostream>
#include <string>

void RemoveFileCommand::execute(const Arguments& arguments)
{
    auto master_password = askpass("Master Password: ");

    _challenge_verifier.verify(std::string(master_password))
        .match(
            [&] (const auto& master_block) {
                auto filename = _encrypter.encrypt(
                    std::string(arguments.remove_file),
                    std::string(master_password),
                    master_block.encryption_iv);

                _api.remove_file(filename)
                    .match(
                        [] (auto&&) -> void {},
                        [&] (const auto& api_failure_reason) -> void {
                            auto failure_reason = _failure_reason_translator.translate(api_failure_reason);
                            std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
                        });
            },
            [&] (const auto& failure_reason) {
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });

    clear_data(master_password);
}

bool RemoveFileCommand::matches(const Arguments& arguments) const
{
    using namespace std::string_literals;
    return arguments.remove_file != ""s;
}
