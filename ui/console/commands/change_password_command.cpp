#include "ui/console/commands/change_password_command.h"

#include <string>

#include "support/arguments.h"
#include "support/askpass.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    using namespace std::string_literals;

    bool ChangePasswordCommand::matches(const Arguments& args)
    {
        return args.change_password_file != ""s;
    }

    void ChangePasswordCommand::execute(const Arguments& args)
    {
        auto new_password = askpass("Password: "s);
        _input.get_master_password()
            .match(
                [&] (auto&& result) {
                    auto& [password, master_block] = result;

                    _inner.execute(
                            args.change_password_file,
                            std::move(new_password),
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
