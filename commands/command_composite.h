#pragma once

#include "commands/command.h"
#include "support/arguments.h"

#include <memory>
#include <vector>

class CommandComposite : public Command
{
    private:
        std::vector<std::unique_ptr<Command>> _commands;

    public:
        CommandComposite(std::vector<std::unique_ptr<Command>>&& commands)
            : _commands(std::move(commands)) {}

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};
