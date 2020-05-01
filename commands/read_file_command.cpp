#include "commands/read_file_command.h"

#include "api/master_block.h"
#include "support/arguments.h"
#include "support/askpass.h"
#include "support/failure_reason_translator.h"

#include <iostream>
#include <string>

void ReadFileCommand::execute(const Arguments& arguments)
{
    auto master_password = askpass("Master Password: ");
    _challenge_verifier.verify(std::string(master_password))
        .match(
            [&] (const auto& master_block)
            {
                auto filename = _encrypter.encrypt(
                    std::string(arguments.read_file),
                    std::string(master_password),
                    master_block.encryption_iv);

                _api.read_file(filename)
                    .match(
                        [&] (const auto& file) -> void {
                            decrypt_file(file, std::move(master_password), master_block);
                        },
                        [&] (const auto& api_failure_reason) -> void {
                            auto failure_reason = _failure_reason_translator.translate(api_failure_reason);
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

void ReadFileCommand::decrypt_file(
        const File& file,
        std::string&& master_password,
        const MasterBlock& master_block)
{
    using namespace std::string_literals;

    auto filename = _decrypter.decrypt(
        file.name,
        std::string(master_password),
        master_block.encryption_iv)
        .match(
            [] (auto&& plaintext) { return plaintext; },
            [] (auto&&) { return ""s; });

    auto username = _decrypter.decrypt(
        file.username,
        std::string(master_password),
        master_block.encryption_iv)
        .match(
            [] (auto&& plaintext) { return plaintext; },
            [] (auto&&) { return ""s; });

    auto password = _decrypter.decrypt(
        file.password,
        std::move(master_password),
        master_block.encryption_iv)
        .match(
            [] (auto&& plaintext) { return plaintext; },
            [] (auto&&) { return ""s; });

    std::cout << filename << std::endl;
    std::cout << username << std::endl;
    std::cout << password << std::endl;
}
