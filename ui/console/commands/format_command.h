#pragma once

#include "commands/format_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"
#include "ui/console/common/input.h"

namespace bf::ui::console::commands {
    class FormatCommand : public Command
    {
        private:
            ::FormatCommand& _inner;
            common::Input& _input;

        public:
            FormatCommand(::FormatCommand& inner, common::Input& input)
                : _inner(inner),
                _input(input)
            {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
