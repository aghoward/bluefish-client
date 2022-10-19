#pragma once

#include "commands/change_username_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"
#include "ui/console/common/input.h"

namespace bf::ui::console::commands {
    class ChangeUsernameCommand : public Command
    {
        private:
            ::ChangeUsernameCommand& _inner;
            common::Input& _input;

        public:
            explicit ChangeUsernameCommand(::ChangeUsernameCommand& inner, common::Input& input)
                : _inner(inner),
                _input(input)
                {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
