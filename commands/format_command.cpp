#include "commands/format_command.h"

#include "support/arguments.h"
#include "support/askpass.h"
#include "support/failure_reason.h"
#include "encryption/encryption_helpers.h"
#include "encryption/encryption.h"
#include "either/either.h"

#include <iostream>
#include <string>

either<std::string, FailureReason> FormatCommand::get_master_password() const
{
    auto master_password = askpass("Master Password:");
    auto retry = askpass("Retype Master Password:");

    if (master_password != retry)
        return FailureReason::PasswordsDoNotMatch;

    clear_data(retry);
    return master_password;
}

std::string FormatCommand::encrypt_challenge(
    std::string&& challenge,
    std::string&& password,
    const std::string& iv) const
{
    return _encrypter.encrypt(
        std::move(challenge),
        std::move(password),
        iv);
}


void FormatCommand::execute(const Arguments&)
{
    auto response = std::string();
    std::cout << "Are you sure you want to format your device? (format/no): " << std::endl;
    std::getline(std::cin, response);
    if (response != "format")
        return;

    auto iv = create_random_iv();
    auto challenge = create_random_iv();

    get_master_password()
        .match(
            [&] (auto&& password) -> void {
                auto encrypted_challenge = encrypt_challenge(
                        std::move(challenge),
                        std::move(password),
                        iv);

                _api.format(iv, encrypted_challenge)
                    .match(
                        [] (const auto&) -> void {},
                        [&] (const auto& api_failure_reason) -> void {
                            auto failure_reason = _failure_reason_translator.translate(api_failure_reason);
                            std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
                        });
            },
            [&] (auto&& failure) -> void {
                std::cout << _failure_reason_translator.to_string(failure) << std::endl;
            });
}

bool FormatCommand::matches(const Arguments& arguments) const
{
    return arguments.format;
}
