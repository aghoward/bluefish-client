#include "ui/console/commands/print_usage_command.h"

#include <iostream>

#include "encryption/encryption_helpers.h"
#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool PrintUsageCommand::matches(const Arguments& args)
    {
        return args.print_usage;
    }

    void PrintUsageCommand::execute(const Arguments&)
    {
        _inner.execute()
            .match(
                [] (auto&& master_block) {
                    std::cout << "Free inodes: " << master_block.free_inodes << std::endl;
                    std::cout << "File count: " << master_block.file_count << std::endl;
                    std::cout << "iv size: " << master_block.encryption_iv.size() << std::endl;
                    std::cout << "iv: " << print_hex(master_block.encryption_iv) << std::endl;
                },
                [] (auto&& failure) { common::write_failure(failure); }
            );
    }
}
