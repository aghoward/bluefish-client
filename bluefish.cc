#include <cstdint>
#include <iostream>
#include <string>
#include <memory>

#include "cdif/cdif.h"
#include "api/api_module.h"
#include "commands/commands_module.h"
#include "encryption/encryption_module.h"
#include "serial/serial_module.h"
#include "support/support_module.h"

#include "support/argument_parsing.h"
#include "support/arguments.h"
#include "commands/command.h"

cdif::Container create_container()
{
    auto container = cdif::Container();
    container.registerModule<CommandsModule>();
    container.registerModule<APIModule>();
    container.registerModule<SerialModule>();
    container.registerModule<SupportModule>();
    container.registerModule<EncryptionModule>();
    return container;
}

int main(int argc, const char* argv[])
{
    std::cout << "Bluefish Password Manager" << std::endl << std::endl;

    auto parser = createArgumentParser();
    auto parseResult = parser.parse(argc, argv);

    return parseResult.match(
        [&] (const auto& arguments) {
            if (arguments.print_help)
            {
                std::cout << parser.help(argv[0]) << std::endl;
                return 0;
            }

            auto container = create_container();
            auto& args = container.resolve<Arguments&>();
            args = arguments;

            auto command = container.resolve<std::unique_ptr<Command>>();

            if (!command->matches(arguments))
            {
                std::cout << "invalid argument configuration" << std::endl;
                return 1;
            }

            command->execute(arguments);
            return 0;
        },
        [&] (const auto& failure) {
            std::cerr << parser.usage(argv[0]) << std::endl;
            std::cerr << parser.get_error_message(failure) << std::endl;
            return 1;
        });
}
