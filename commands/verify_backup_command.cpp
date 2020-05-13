#include "commands/verify_backup_command.h"

#include "commands/common/read_backup_file.h"
#include "support/arguments.h"

#include <iostream>
#include <string>

bool VerifyBackupCommand::matches(const Arguments& args) const
{
    using namespace std::string_literals;
    return args.verify != ""s;
}

void VerifyBackupCommand::execute(const Arguments& args)
{
    bf::read_backup_file(args.verify)
        .match(
            [] (const auto& backup) -> void {
                std::cout << "Master block file count: " << backup.master_block.file_count << std::endl;
                std::cout << "Master block free inodes: " << backup.master_block.free_inodes << std::endl;
                std::cout << "Initialization vector size: " << backup.master_block.encryption_iv.size() << std::endl;
                std::cout << "Files found: " << backup.files.size() << std::endl;
            },
            [&] (const auto& failure) -> void {
                std::cerr << _failure_reason_translator.to_string(failure) << std::endl;
            });
}
