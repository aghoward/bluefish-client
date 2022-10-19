#include "commands/change_password_command.h"

#include <string>

#include "api/api.h"
#include "api/master_block.h"
#include "support/success.h"

either<bf::Success, FailureReason> ChangePasswordCommand::execute(
        const std::string& filename,
        std::string&& new_password,
        std::string&& master_password,
        const std::string& encryption_iv)
{
    auto encrypted_filename = _encrypter.encrypt(
        std::string(filename),
        std::string(master_password),
        encryption_iv);

    return _api.read_file(encrypted_filename)
        .mapSecond(
            [&] (const APIFailureReason& failure) -> FailureReason {
                return _failure_reason_translator.translate(failure);
        })
        .foldFirst([&] (auto&& file) {
            file.password = _encrypter.encrypt(
                std::move(new_password),
                std::move(master_password),
                encryption_iv);

            return _api.remove_file(encrypted_filename)
                .foldFirst(
                    [&] (auto&&) {
                        return _api.write_file(file);
                    })
                .mapSecond(
                    [&] (const APIFailureReason& failure) -> FailureReason {
                        return _failure_reason_translator.translate(failure);
                });
        })
        .mapFirst(
            [] (const auto&) -> bf::Success { return {}; }
        );
}

