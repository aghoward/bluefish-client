#include "ui/console/commands/command_composite.h"

#include <algorithm>

#include "support/arguments.h"

namespace bf::ui::console::commands {
    bool CommandComposite::matches(const Arguments& args)
    {
        return std::find_if(
                std::begin(_commands),
                std::end(_commands),
                [&] (const auto& command) { return command->matches(args); })
            != std::end(_commands);
    }

    void CommandComposite::execute(const Arguments& args)
    {
        const auto& command = std::find_if(
                std::begin(_commands),
                std::end(_commands),
                [&] (const auto& c) { return c->matches(args); });
        (*command)->execute(args);
    }
}
