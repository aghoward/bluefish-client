#include "commands/format_command.h"

#include "support/arguments.h"
#include "encryption/encryption_helpers.h"

#include <iostream>
#include <string>

void FormatCommand::execute(const Arguments&)
{
    auto response = std::string();
    std::cout << "Are you sure you want to format your device? (format/no): " << std::endl;
    std::cin >> response;
    if (response != "format")
        return;

    auto iv = create_random_iv();

    _api.format(iv)
        .match(
            [] (const auto&) -> void {},
            [&] (const auto& failure_reason) -> void {
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });
}

bool FormatCommand::matches(const Arguments& arguments) const
{
    return arguments.format;
}
