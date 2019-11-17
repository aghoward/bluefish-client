#include "commands/print_usage_command.h"

#include "support/arguments.h"
#include "encryption/encryption_helpers.h"

#include <iostream>

void PrintUsageCommand::execute(const Arguments&)
{
    _api.get_master_block()
        .match(
            [] (const auto& master_block)
            {
                std::cout << std::hex;
                std::cout << "Free inodes: " << master_block.free_inodes << std::endl;
                std::cout << "File count: " << master_block.file_count << std::endl;
                std::cout << std::dec;
                std::cout << "iv size: " << master_block.encryption_iv.size() << std::endl;
                std::cout << "iv: " << print_hex(master_block.encryption_iv) << std::endl;
            },
            [&] (const auto& api_failure_reason)
            {
                auto failure_reason = _failure_reason_translator.translate(api_failure_reason);
                std::cout << _failure_reason_translator.to_string(failure_reason) << std::endl;
            });
}

bool PrintUsageCommand::matches(const Arguments& arguments) const
{
    return arguments.print_usage;
}
