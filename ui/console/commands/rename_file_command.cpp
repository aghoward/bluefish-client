#include "ui/console/commands/rename_file_command.h"

#include <iostream>
#include <string>

#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool RenameFileCommand::matches(const Arguments& args)
    {
        using namespace std::string_literals;
        return args.rename_file != ""s && args.new_file_name != ""s;
    }

    void RenameFileCommand::execute(const Arguments& args)
    {
        _input.get_master_password()
            .match(
                [&] (auto&& result) {
                    auto& [password, master_block] = result;
                    _inner.execute(
                            args.rename_file,
                            args.new_file_name,
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
