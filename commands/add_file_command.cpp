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
    auto master_password = askpass("Master Password:");
    auto retry = askpass("Retype Master Password:");

    if (master_password != retry)
    {
        std::cout << "Master passwords do not match!" << std::endl;
        return;
    }

    _api.get_master_block()
        .match(
            [&] (const auto& master_block)
            {
                auto encrypted_password = _encrypter.encrypt(
                        std::move(password),
                        std::move(master_password),
                        master_block.encryption_iv);

                _api.write_file({ arguments.add_file, arguments.username, encrypted_password })
                    .match(
                        [] (const auto&) -> void { },
                        [&] (const auto& failure_reason) -> void {
                            std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
                        });
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
