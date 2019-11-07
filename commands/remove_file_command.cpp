#include "commands/remove_file_command.h"

#include "support/arguments.h"

#include <iostream>
#include <string>

void RemoveFileCommand::execute(const Arguments& arguments)
{
    _api.remove_file(arguments.remove_file)
        .match(
            [] (const auto&) -> void {},
            [&] (const auto& failure_reason) -> void {
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });
}

bool RemoveFileCommand::matches(const Arguments& arguments) const
{
    using namespace std::string_literals;
    return arguments.remove_file != ""s;
}
