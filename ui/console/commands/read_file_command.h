#pragma once

#include "commands/read_file_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"
#include "ui/console/common/input.h"

namespace bf::ui::console::commands {
    class ReadFileCommand : public Command
    {
        private:
            ::ReadFileCommand& _inner;
            common::Input& _input;

        public:
            ReadFileCommand(::ReadFileCommand& inner, common::Input& input)
                : _inner(inner),
                _input(input)
            {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
