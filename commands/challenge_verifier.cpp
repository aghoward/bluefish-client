#include "challenge_verifier.h"

#include <string>

#include "either/either.h"
#include "api/api.h"
#include "support/failure_reason.h"

either<MasterBlock, FailureReason> ChallengeVerifier::verify(std::string&& password)
{
    return _api.get_master_block()
        .match(
            [&] (auto&& master_block) -> either<MasterBlock, FailureReason>
            {
                auto challenge = master_block.challenge;
                return _decrypter.decrypt(
                        challenge,
                        std::move(password),
                        master_block.encryption_iv)
                    .match(
                        [&] (auto&&) -> either<MasterBlock, FailureReason>
                        {
                            return master_block;
                        },
                        [&] (auto&& failure) -> either<MasterBlock, FailureReason>
                        {
                            return _failure_reason_translator.translate(failure);
                        }
                    );
            },
            [&] (auto&& failure) -> either<MasterBlock, FailureReason>
            {
                return _failure_reason_translator.translate(failure);
            });
}
