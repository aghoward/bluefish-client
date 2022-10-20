#pragma once

#include "commands/restore_backup_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"

namespace bf::ui::console::commands {
    class RestoreBackupCommand : public Command
    {
        private:
            ::RestoreBackupCommand& _inner;

        public:
            explicit RestoreBackupCommand(::RestoreBackupCommand& inner)
                : _inner(inner)
            {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
