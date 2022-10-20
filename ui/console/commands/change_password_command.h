#pragma once

#include "commands/change_password_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"
#include "ui/console/common/input.h"

namespace bf::ui::console::commands {
    class ChangePasswordCommand : public Command
    {
        private:
            ::ChangePasswordCommand& _inner;
            common::Input& _input;

        public:
            ChangePasswordCommand(::ChangePasswordCommand& inner, common::Input& input)
                : _inner(inner),
                _input(input)
            {}

            void execute(const Arguments& args) override;
            bool matches(const Arguments& args) override;
    };
}
