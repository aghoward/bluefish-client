#pragma once

#include "commands/add_file_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"
#include "ui/console/common/input.h"

namespace bf::ui::console::commands {
    class AddFileCommand : public Command
    {
        private:
            ::AddFileCommand& _inner;
            common::Input& _input;

        public:
            AddFileCommand(::AddFileCommand& inner, common::Input& input)
                : _inner(inner),
                _input(input)
            {}

            void execute(const Arguments& args) override;
            bool matches(const Arguments& args) override;
    };
}
