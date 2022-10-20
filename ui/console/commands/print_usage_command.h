#pragma once

#include "commands/print_usage_command.h"
#include "support/arguments.h"
#include "ui/console/commands/command.h"

namespace bf::ui::console::commands {
    class PrintUsageCommand : public Command
    {
        private:
            ::PrintUsageCommand& _inner;

        public:
            explicit PrintUsageCommand(::PrintUsageCommand& inner)
                : _inner(inner)
            {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
