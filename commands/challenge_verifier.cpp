#include "challenge_verifier.h"

#include <optional>
#include <string>
#include <tuple>

#include "either/either.h"
#include "api/api.h"
#include "api/master_block.h"
#include "support/askpass.h"
#include "support/failure_reason.h"

either<std::string, FailureReason> ChallengeVerifier::verify_entered_password(const MasterBlock& master_block) const
{
    auto password = std::string{};
    auto failure = std::optional<FailureReason>{};
    for (auto attempt = 0; (attempt < 3 && failure) || attempt == 0; attempt++)
    {
        password = askpass("Master Password: ");
        failure = _decrypter.decrypt(
                master_block.challenge,
                std::string(password),
                master_block.encryption_iv)
            .match(
                [&] (auto&&) -> decltype(failure) { return {}; },
                [&] (auto&& f) -> decltype(failure) { return _failure_reason_translator.translate(f); });
    }

    if (failure)
        return failure.value();
    return password;
}

either<std::tuple<MasterBlock, std::string>, FailureReason> ChallengeVerifier::verify() const
{
    return _api.get_master_block()
        .match(
            [&] (auto&& master_block) -> either<std::tuple<MasterBlock, std::string>, FailureReason>
            {
                return verify_entered_password(master_block)
                    .mapFirst(
                        [&] (auto&& password)
                        {
                            return std::make_tuple(std::move(master_block), password);
                        });
            },
            [&] (auto&& failure) -> either<std::tuple<MasterBlock, std::string>, FailureReason>
            {
                return _failure_reason_translator.translate(failure);
            });
}
