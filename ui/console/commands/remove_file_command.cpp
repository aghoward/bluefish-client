#include "ui/console/commands/remove_file_command.h"

#include <iostream>
#include <string>

#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool RemoveFileCommand::matches(const Arguments& args)
    {
        using namespace std::string_literals;
        return args.remove_file != ""s;
    }

    void RemoveFileCommand::execute(const Arguments& args)
    {
        _input.get_master_password()
            .match(
                [&] (auto&& result) {
                    auto& [password, master_block] = result;
                    _inner.execute(
                            args.remove_file,
                            std::move(password),
                            master_block.encryption_iv)
                        .match(
                            [] (auto&&) {},
                            [] (auto&& failure) { common::write_failure(failure); }
                        );
                },
                [] (auto&& failure) { common::write_failure(failure); }
            );
    }
}
