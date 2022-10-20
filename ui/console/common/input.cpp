#include "ui/console/common/input.h"

#include <optional>
#include <string>
#include <tuple>

#include "api/master_block.h"
#include "commands/verify_challenge_command.h"
#include "either/either.h"
#include "encryption/encryption_helpers.h"
#include "support/askpass.h"

namespace bf::ui::console::common {
    either<std::tuple<std::string, MasterBlock>, ChallengeFailure> Input::get_master_password()
    {
        const auto retry_attempts = 3;
        std::optional<MasterBlock> master_block = {};
        std::optional<ChallengeFailure> failure = {};
        std::string password = "";

        for (auto attempt = 0; !master_block && attempt < retry_attempts; attempt++)
        {
            clear_data(password);
            password = askpass("Master Password: ");
            _challenge_verifier.verify(password)
                .match(
                    [&] (auto&& block) { master_block = block; },
                    [&] (auto&& f) { failure = f; }
                );
        }
        
        if (!master_block)
            return failure.value();
        return std::make_tuple(std::move(password), std::move(master_block.value()));
    }
}
