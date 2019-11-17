#include "commands/list_files_command.h"

#include "support/arguments.h"

#include <algorithm>
#include <iostream>

void ListFilesCommand::execute(const Arguments&)
{
    _api.list_files()
        .match(
            [] (auto&& filenames)
            {
                std::sort(
                    filenames.begin(),
                    filenames.end(),
                    [] (const auto& first, const auto& second) {
                        return first < second;
                    });
                for (auto& filename : filenames)
                    std::cout << filename << std::endl;
            },
            [&] (const auto& api_failure_reason)
            {
                auto failure_reason = _failure_reason_translator.translate(api_failure_reason);
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });
}

bool ListFilesCommand::matches(const Arguments& arguments) const
{
    return arguments.list;
}
