#include "commands/rename_file_command.h"

#include <string>

#include "either/either.h"
#include "support/failure_reason.h"
#include "support/success.h"

either<bf::Success, FailureReason> RenameFileCommand::execute(
        const std::string& old_filename,
        const std::string& new_filename,
        std::string&& master_password,
        const std::string& encryption_iv)
{
    auto encrypted_filename = _encrypter.encrypt(
        std::string(old_filename),
        std::string(master_password),
        encryption_iv);

    return _api.read_file(encrypted_filename)
        .foldFirst([&] (auto&& file) {
            file.name = _encrypter.encrypt(
                std::string(new_filename),
                std::string(master_password),
                encryption_iv);

            return _api.write_file(file);
        })
        .foldFirst([&] (auto&&) {
            return _api.remove_file(encrypted_filename);
        })
        .map(
            [] (auto&&) -> bf::Success { return {}; },
            [&] (const APIFailureReason& failure) -> FailureReason {
                return _failure_reason_translator.translate(failure);
            }
        );
}

