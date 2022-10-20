#pragma once

#include "commands/create_backup_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"
#include "ui/console/common/input.h"

namespace bf::ui::console::commands {
    class CreateBackupCommand : public Command
    {
        private:
            ::CreateBackupCommand& _inner;
            common::Input& _input;

        public:
            CreateBackupCommand(::CreateBackupCommand& inner, common::Input& input)
                : _inner(inner),
                _input(input)
            {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
