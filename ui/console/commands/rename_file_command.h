#pragma once

#include "commands/rename_file_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"
#include "ui/console/common/input.h"

namespace bf::ui::console::commands {
    class RenameFileCommand : public Command
    {
        private:
            ::RenameFileCommand& _inner;
            common::Input& _input;

        public:
            RenameFileCommand(::RenameFileCommand& inner, common::Input& input)
                : _inner(inner),
                _input(input)
            {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
