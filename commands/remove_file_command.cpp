#include "commands/remove_file_command.h"

#include <string>

#include "encryption/encryption_helpers.h"
#include "support/success.h"

either<bf::Success, FailureReason> RemoveFileCommand::execute(
        const std::string& filename,
        std::string&& master_password,
        const std::string& encryption_iv)
{
    auto encrypted_filename = _encrypter.encrypt(
        std::string(filename),
        std::move(master_password),
        encryption_iv);

    return _api.remove_file(encrypted_filename)
        .map(
            [] (auto&&) -> bf::Success { return {}; },
            [&] (const auto& api_failure_reason) -> FailureReason {
                return _failure_reason_translator.translate(api_failure_reason);
            });
}

