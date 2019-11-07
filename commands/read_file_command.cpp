#include "commands/read_file_command.h"

#include "support/arguments.h"
#include "support/askpass.h"
#include "support/failure_reason_translator.h"

#include <iostream>
#include <string>

void ReadFileCommand::execute(const Arguments& arguments)
{
    _api.get_master_block()
        .match(
            [&] (const auto& master_block)
            {
                auto master_password = askpass("Master Password:");
                _api.read_file(arguments.read_file)
                    .match(
                        [&] (const auto& file) -> void {
                            auto password = _decrypter.decrypt(
                                    file.password,
                                    std::move(master_password),
                                    master_block.encryption_iv);
                            std::cout << "Filename: " << file.name << std::endl;
                            std::cout << "Username: " << file.username << std::endl;
                            std::cout << "Password: " << password << std::endl;
                        },
                        [&] (const auto& failure_reason) -> void {
                            std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
                        });
            },
            [&] (const auto& failure_reason) {
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });
}

bool ReadFileCommand::matches(const Arguments& arguments) const
{
    using namespace std::string_literals;
    return arguments.read_file != ""s;
}
