#include "commands/change_username_command.h"

#include <string>

#include "api/api.h"
#include "api/master_block.h"
#include "support/failure_reason.h"
#include "support/success.h"

either<bf::Success, FailureReason> ChangeUsernameCommand::execute(
        const std::string& filename,
        std::string&& username,
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
            file.username = _encrypter.encrypt(
                std::move(username),
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

