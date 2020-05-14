#include "commands/change_username_command.h"

#include "api/api.h"
#include "api/master_block.h"
#include "support/arguments.h"
#include "support/askpass.h"

#include <iostream>
#include <string>

bool ChangeUsernameCommand::matches(const Arguments& arguments) const
{
    using namespace std::string_literals;
    return arguments.change_username_file != ""s && arguments.username != ""s;
}

void ChangeUsernameCommand::execute(const Arguments& arguments)
{
    auto master_password = askpass("Master Password: ");

    MasterBlock master_block;
    std::string filename;
    File new_file;

    _challenge_verifier.verify(std::string(master_password))
        .foldFirst([&] (const auto& mb) {
            master_block = mb;

            filename = _encrypter.encrypt(
                std::string(arguments.change_username_file),
                std::string(master_password),
                master_block.encryption_iv);

            return _api.read_file(filename)
                .mapSecond(
                    [&] (const APIFailureReason& failure) -> FailureReason {
                        return _failure_reason_translator.translate(failure);
                });
        })
        .foldFirst([&] (const auto& file) {
            new_file = file;
            new_file.username = _encrypter.encrypt(
                std::string(arguments.username),
                std::string(master_password),
                master_block.encryption_iv);

            return _api.remove_file(filename)
                .mapSecond(
                    [&] (const APIFailureReason& failure) -> FailureReason {
                        return _failure_reason_translator.translate(failure);
                });
        })
        .foldFirst([&] (const auto&) {
            return _api.write_file(new_file)
                .mapSecond(
                    [&] (const APIFailureReason& failure) -> FailureReason {
                        return _failure_reason_translator.translate(failure);
                });
        })
        .match(
            [] (const auto&) -> void {},
            [&] (const auto& failure_reason) -> void {
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
        });
}

