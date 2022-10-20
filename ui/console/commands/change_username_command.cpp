#include "ui/console/commands/change_username_command.h"

#include <string>

#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    using namespace std::string_literals;

    bool ChangeUsernameCommand::matches(const Arguments& args)
    {
        return args.change_username_file != ""s && args.username != ""s;
    }

    void ChangeUsernameCommand::execute(const Arguments& args)
    {
        _input.get_master_password()
            .match(
                [&] (auto&& result) {
                    auto& [password, master_block] = result;
                    _inner.execute(
                            args.change_username_file,
                            std::string(args.username),
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
