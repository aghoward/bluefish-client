#include "commands/command_composite.h"

#include "support/arguments.h"

#include <algorithm>

void CommandComposite::execute(const Arguments& arguments)
{
    for (auto& command : _commands)
        if (command->matches(arguments))
            command->execute(arguments);
}

bool CommandComposite::matches(const Arguments& arguments) const
{
    auto it = std::find_if(
        _commands.begin(),
        _commands.end(),
        [&] (const auto& command) { return command->matches(arguments); });
    return it != _commands.end();
}
