#pragma once

#include <string>
#include <tuple>

#include "api/master_block.h"
#include "commands/verify_challenge_command.h"
#include "either/either.h"

namespace bf::ui::console::common {
    class Input {
        private:
            VerifyChallengeCommand& _challenge_verifier;

        public:
            explicit Input(VerifyChallengeCommand& cv)
                : _challenge_verifier(cv)
            {}

            either<std::tuple<std::string, MasterBlock>, ChallengeFailure> get_master_password();
    };
}
