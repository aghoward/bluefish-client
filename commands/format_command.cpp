#include "commands/format_command.h"

#include <string>

#include "either/either.h"
#include "encryption/encryption_helpers.h"
#include "support/failure_reason.h"
#include "support/success.h"

either<bf::Success, FailureReason> FormatCommand::execute(std::string&& password)
{
    auto iv = create_random_iv();
    auto challenge = create_random_iv();

    auto encrypted_challenge = _encrypter.encrypt(
            std::move(challenge),
            std::move(password),
            iv);

    return _api.format(iv, encrypted_challenge)
        .map(
            [] (const auto&) -> bf::Success { return {}; },
            [&] (const auto& api_failure_reason) -> FailureReason {
                return _failure_reason_translator.translate(api_failure_reason);
            });
}
