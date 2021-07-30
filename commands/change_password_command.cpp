#include "commands/change_password_command.h"

#include "api/api.h"
#include "api/master_block.h"
#include "support/arguments.h"
#include "support/askpass.h"

#include <iostream>
#include <string>
#include <tuple>

bool ChangePasswordCommand::matches(const Arguments& arguments) const
{
    using namespace std::string_literals;
    return arguments.change_password_file != ""s;
}

void ChangePasswordCommand::execute(const Arguments& arguments)
{
    MasterBlock master_block;
    std::string filename;
    File new_file;

    _challenge_verifier.verify()
        .foldFirst([&] (auto&& result) {
            auto& [mb, master_password] = result;
            master_block = mb;

            filename = _encrypter.encrypt(
                std::string(arguments.change_password_file),
                std::string(master_password),
                master_block.encryption_iv);

            return _api.read_file(filename)
                .mapFirst(
                    [&] (const auto& file) { return std::make_tuple(file, std::move(master_password)); }
                ).mapSecond(
                    [&] (const APIFailureReason& failure) -> FailureReason {
                        return _failure_reason_translator.translate(failure);
                });
        })
        .foldFirst([&] (auto&& result) {
            auto& [file, master_password] = result;
            new_file = file;
            new_file.password = _encrypter.encrypt(
                askpass(),
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

