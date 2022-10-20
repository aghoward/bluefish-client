#pragma once

#include "commands/verify_backup_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"

namespace bf::ui::console::commands {
    class VerifyBackupCommand : public Command
    {
        private:
            ::VerifyBackupCommand& _inner;

        public:
            explicit VerifyBackupCommand(::VerifyBackupCommand& inner)
                : _inner(inner)
            {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
