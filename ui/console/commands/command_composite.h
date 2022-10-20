#pragma once

#include <memory>
#include <vector>

#include "support/arguments.h"
#include "ui/console/commands/command.h"

namespace bf::ui::console::commands {
    class CommandComposite : public Command {
        private:
            std::vector<std::unique_ptr<Command>> _commands;

        public:
            explicit CommandComposite(std::vector<std::unique_ptr<Command>>&& commands)
                : _commands(std::move(commands))
            {}

            bool matches(const Arguments& args) override;
            void execute(const Arguments& args) override;
    };
}
