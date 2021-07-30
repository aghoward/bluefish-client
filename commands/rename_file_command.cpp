#include "commands/rename_file_command.h"

#include "api/api.h"
#include "api/master_block.h"
#include "support/arguments.h"
#include "support/askpass.h"

#include <iostream>
#include <string>

bool RenameFileCommand::matches(const Arguments& arguments) const
{
    using namespace std::string_literals;
    return arguments.rename_file != ""s && arguments.new_file_name != ""s;
}

void RenameFileCommand::execute(const Arguments& arguments)
{
    MasterBlock master_block;

    _challenge_verifier.verify()
        .foldFirst([&] (auto&& result) {
            auto& [mb, master_password] = result;
            master_block = mb;

            auto filename = _encrypter.encrypt(
                std::string(arguments.rename_file),
                std::string(master_password),
                master_block.encryption_iv);

            return _api.read_file(filename)
                .mapFirst(
                    [&] (const auto& file) { return std::make_tuple(file, master_password); }
                ).mapSecond(
                    [&] (const APIFailureReason& failure) -> FailureReason {
                        return _failure_reason_translator.translate(failure);
                });
        })
        .foldFirst([&] (auto&& result) {
            auto& [file, master_password] = result;
            auto new_file = file;
            auto new_file_name = _encrypter.encrypt(
                std::string(arguments.new_file_name),
                std::string(master_password),
                master_block.encryption_iv);
            new_file.name = new_file_name;

            return _api.write_file(new_file)
                .mapFirst([&] (const auto&) { return std::move(master_password); })
                .mapSecond(
                    [&] (const APIFailureReason& failure) -> FailureReason {
                        return _failure_reason_translator.translate(failure);
                });
        })
        .foldFirst([&] (auto&& master_password) {
            auto filename = _encrypter.encrypt(
                std::string(arguments.rename_file),
                std::move(master_password),
                master_block.encryption_iv);

            return _api.remove_file(filename)
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

