#include "ui/console/commands/read_file_command.h"

#include <iostream>
#include <string>

#include "support/arguments.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool ReadFileCommand::matches(const Arguments& args)
    {
        using namespace std::string_literals;
        return args.read_file != ""s;
    }

    void ReadFileCommand::execute(const Arguments& args)
    {
        _input.get_master_password()
            .match(
                [&] (auto&& result) {
                    auto& [password, master_block] = result;
                    _inner.execute(
                            args.read_file,
                            std::move(password),
                            master_block.encryption_iv)
                        .match(
                            [] (auto&& file) {
                                std::cout << file.filename << std::endl;
                                std::cout << file.username << std::endl;
                                std::cout << file.password << std::endl;
                            },
                            [] (auto&& failure) { common::write_failure(failure); }
                        );
                },
                [] (auto&& failure) { common::write_failure(failure); }
            );
    }
}
