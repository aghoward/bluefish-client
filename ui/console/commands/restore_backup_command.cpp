#include "ui/console/commands/restore_backup_command.h"

#include <iostream>
#include <string>

#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool RestoreBackupCommand::matches(const Arguments& args)
    {
        using namespace std::string_literals;
        return args.restore_file != ""s;
    }

    bool query_user_confidence()
    {
        using namespace std::string_literals;

        auto response = std::string();
        std::cout << "Are you sure you want to erase your device and restore the backup file? (yes/no): " << std::endl;
        std::getline(std::cin, response);
        return response == "yes"s;
    }

    void RestoreBackupCommand::execute(const Arguments& args)
    {
        if (!query_user_confidence())
            return;

        _inner.execute(args.restore_file)
            .match(
                [] (auto&&) {},
                [] (auto&& failure) { common::write_failure(failure); }
            );
    }
}
