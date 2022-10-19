#include "ui/console/commands/create_backup_command.h"

#include <string>

#include "encryption/encryption_helpers.h"
#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    using namespace std::string_literals;

    bool CreateBackupCommand::matches(const Arguments& args)
    {
        return args.backup_file != ""s;
    }

    void CreateBackupCommand::execute(const Arguments& args)
    {
        _input.get_master_password()
            .match(
                [&] (auto&& result) {
                    auto& [password, master_block] = result;
                    clear_data(password);
                    _inner.execute(master_block, args.backup_file)
                        .match(
                            [] (auto&&) {},
                            [] (auto&& failure) { common::write_failure(failure); }
                        );
                },
                [] (auto&& failure) { common::write_failure(failure); }
            );
    }
}
