#include "commands/add_file_command.h"

#include "support/arguments.h"
#include "support/askpass.h"

#include <iostream>
#include <string>

void AddFileCommand::execute(const Arguments& arguments)
{
    using namespace std::string_literals;

    if (arguments.username == ""s)
    {
        std::cout << 
            "Username is required when adding a file!" <<
            std::endl;
        return;
    }

    auto password = askpass();

    _challenge_verifier.verify()
        .match(
            [&] (auto&& result)
            {
                auto& [master_block, master_password] = result;
                auto encrypted_filename = _encrypter.encrypt(
                        std::string(arguments.add_file),
                        std::string(master_password),
                        master_block.encryption_iv);
                auto encrypted_username = _encrypter.encrypt(
                        std::string(arguments.username),
                        std::string(master_password),
                        master_block.encryption_iv);
                auto encrypted_password = _encrypter.encrypt(
                        std::move(password),
                        std::move(master_password),
                        master_block.encryption_iv);
                write_file(encrypted_filename, encrypted_username, encrypted_password);
            },
            [&] (const auto& failure_reason)
            {
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });
}

bool AddFileCommand::matches(const Arguments& arguments) const
{
    using namespace std::string_literals;
    return arguments.add_file != ""s;
}

void AddFileCommand::write_file(
        const std::string& filename,
        const std::string& username,
        const std::string& password)
{

    _api.write_file({ filename, username, password })
        .match(
            [] (const auto&) -> void { },
            [&] (const auto& api_failure_reason) -> void {
                auto failure_reason = _failure_reason_translator.translate(api_failure_reason);
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });

}
