#include "ui/console/commands/format_command.h"

#include <string>

#include "either/either.h"
#include "encryption/encryption_helpers.h"
#include "support/arguments.h"
#include "support/askpass.h"
#include "support/failure_reason.h"
#include "ui/console/common/output.h"

namespace bf::ui::console::commands {
    bool FormatCommand::matches(const Arguments& args)
    {
        return args.format;
    }

    either<std::string, FormatFailure> get_new_password()
    {
        using namespace std::string_literals;
        auto first_password = askpass("Password: "s);
        auto second_password = askpass("Re-enter Password: "s);
        if (first_password != second_password)
            return FormatFailure::PasswordsDoNotMatch;
        clear_data(second_password);
        return first_password;
    }

    bool prompt_user()
    {
        using namespace std::string_literals;

        auto response = std::string();
        std::cout << "Are you sure you want to format the device and erase all data? (format/no): " << std::endl;
        std::getline(std::cin, response);
        return response == "format"s;
    }

    void FormatCommand::execute(const Arguments&)
    {
        if (!prompt_user())
            return;

        get_new_password()
            .match(
                [&] (auto&& password) {
                    _inner.execute(std::move(password))
                        .match(
                            [] (auto&&) {},
                            [] (auto&& failure) { common::write_failure(failure); }
                        );
                },
                [] (auto&& failure) { common::write_failure(failure); }
            );
    }
}
