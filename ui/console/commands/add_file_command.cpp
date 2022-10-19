#include "ui/console/commands/add_file_command.h"

#include <iostream>

#include "support/askpass.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool AddFileCommand::matches(const Arguments& args)
    {
        using namespace std::string_literals;
        return args.add_file != ""s;
    }

    void AddFileCommand::execute(const Arguments& args)
    {
        auto new_password = askpass("Password: ");

        _input.get_master_password()
            .match(
                [&] (auto&& result) {
                    auto& [password, master_block] = result;
                    _inner.execute(
                            args.add_file,
                            args.username,
                            std::move(new_password),
                            std::move(password),
                            master_block.encryption_iv)
                        .match(
                            [] (auto&&) {},
                            [] (auto&& failure) { common::write_failure(failure); }
                        );
                },
                [&] (auto&& challenge_failure) { common::write_failure(challenge_failure); }
            );
    }
}
