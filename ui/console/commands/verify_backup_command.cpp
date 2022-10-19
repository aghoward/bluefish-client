#include "ui/console/commands/verify_backup_command.h"

#include <iostream>
#include <string>

#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool VerifyBackupCommand::matches(const Arguments& args)
    {
        using namespace std::string_literals;
        return args.verify != ""s;
    }

    void VerifyBackupCommand::execute(const Arguments& args)
    {
        _inner.execute(args.verify)
            .match(
                [] (auto&& backup) {
                    std::cout << "Master block file count: " << backup.master_block.file_count << std::endl;
                    std::cout << "Master block free inodes: " << backup.master_block.free_inodes << std::endl;
                    std::cout << "Initialization vector size: " << backup.master_block.encryption_iv.size() << std::endl;
                    std::cout << "Files found: " << backup.files.size() << std::endl;
                },
                [] (auto&& failure) { common::write_failure(failure); }
            );
    }
}
