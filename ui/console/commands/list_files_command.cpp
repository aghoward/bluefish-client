#include "ui/console/commands/list_files_command.h"

#include <iostream>

#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool ListFilesCommand::matches(const Arguments& args)
    {
        return args.list;
    }

    void ListFilesCommand::execute(const Arguments&)
    {
        _input.get_master_password()
            .match(
                [&] (auto&& result) {
                    auto& [password, master_block] = result;
                    _inner.execute(master_block, std::move(password))
                        .match(
                            [] (auto&& files) {
                                for (const auto& file : files)
                                    std::cout << file << std::endl;
                            },
                            [] (auto&& failure) { common::write_failure(failure); }
                        );
                },
                [] (auto&& failure) { common::write_failure(failure); }
            );
    }
}
