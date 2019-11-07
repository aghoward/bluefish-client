#include "support/argument_parsing.h"

#include "argparsing/argument_parser.h"
#include "argparsing/argument_parser_builder.h"
#include "support/arguments.h"

#include <string>

ap::ArgumentParser<Arguments> createArgumentParser()
{
    using namespace std::string_literals;

    return ap::ArgumentParserBuilder<Arguments>()
        .add_positional(
            "device"s,
            &Arguments::device,
            ""s,
            "Serial device to connect to"s)
        .add_optional(
            "baud"s,
            &Arguments::baud,
            115200u,
            { "-b"s, "--baud"s },
            "Baud rate for the device"s)
        .add_optional(
            "list"s,
            &Arguments::list,
            false,
            { "-l"s, "--list"s },
            "List files from device"s)
        .add_optional(
            "add_file"s,
            &Arguments::add_file,
            ""s,
            { "-a"s, "--add"s },
            "Add file to device storage"s)
        .add_optional(
            "username"s,
            &Arguments::username,
            ""s,
            { "-u"s, "--username"s },
            "Username for file to add (used with --add)"s)
        .add_optional(
            "remove"s,
            &Arguments::remove_file,
            ""s,
            { "-d"s, "--remove", "--rm" },
            "Remove file from storage"s)
        .add_optional(
            "read"s,
            &Arguments::read_file,
            ""s,
            { "-r"s, "--read"s },
            "Read a file from storage"s)
        .add_optional(
            "format"s,
            &Arguments::format,
            false,
            { "-f"s, "--format"s },
            "Format device"s)
        .add_optional(
            "print_usage"s,
            &Arguments::print_usage,
            false,
            { "-p"s, "--print-usage"s },
            "Print disk usage"s)
        .build();
}

