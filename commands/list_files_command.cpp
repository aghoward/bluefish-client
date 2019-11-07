#include "commands/list_files_command.h"

#include "support/arguments.h"

#include <iostream>

void ListFilesCommand::execute(const Arguments&)
{
    _api.list_files()
        .match(
            [] (const auto& filenames)
            {
                for (auto& filename : filenames)
                    std::cout << filename << std::endl;
            },
            [&] (const auto& failure_reason)
            {
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });
}

bool ListFilesCommand::matches(const Arguments& arguments) const
{
    return arguments.list;
}
