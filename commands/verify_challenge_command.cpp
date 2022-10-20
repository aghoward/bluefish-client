#include <string>

#include "api/api.h"
#include "api/master_block.h"
#include "commands/verify_challenge_command.h"
#include "either/either.h"

either<bf::Success, ChallengeFailure> VerifyChallengeCommand::verify_entered_password(
        const MasterBlock& master_block,
        const std::string& password) const
{
    return _decrypter.decrypt(
            master_block.challenge,
            std::string(password),
            master_block.encryption_iv)
        .map(
            [] (auto&&) -> bf::Success { return {}; },
            [] (auto&&) -> ChallengeFailure { return ChallengeFailure::InvalidPassword; });
}

either<MasterBlock, ChallengeFailure> VerifyChallengeCommand::verify(const std::string& password) const
{
    return _api.get_master_block()
        .match(
            [&] (auto&& master_block) -> either<MasterBlock, ChallengeFailure>
            {
                return verify_entered_password(master_block, password)
                    .mapFirst(
                        [&] (auto&&)
                        {
                            return master_block;
                        });
            },
            [&] (auto&& failure) -> either<MasterBlock, ChallengeFailure>
            {
                return ChallengeFailure(failure);
            });
}
