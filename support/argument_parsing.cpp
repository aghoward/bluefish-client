#include "support/argument_parsing.h"

#include "argparsing/argument_parser.h"
#include "argparsing/argument_parser_builder.h"
#include "support/arguments.h"

#include <string>

ap::ArgumentParser<Arguments> createArgumentParser()
{
    using namespace std::string_literals;

    return ap::ArgumentParserBuilder<Arguments>()
        .add_optional(
            "device"s,
            &Arguments::device,
            "/dev/ttyUSB0"s,
            { "-d"s, "--device"s },
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
            { "--remove"s, "--rm"s },
            "Remove file from storage"s)
        .add_optional(
            "read"s,
            &Arguments::read_file,
            ""s,
            { "-r"s, "--read"s },
            "Read a file from storage"s)
        .add_optional(
            "rename_file"s,
            &Arguments::rename_file,
            ""s,
            { "-e"s, "--rename"s },
            "Rename a file to `new_file_name`"s)
        .add_optional(
            "new_file_name"s,
            &Arguments::new_file_name,
            ""s,
            { "-n"s, "--new-file"s },
            "New name for file being renamed"s)
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
        .add_optional(
            "backup_file"s,
            &Arguments::backup_file,
            ""s,
            { "--backup"s },
            "Backup data from device to local filesystem"s)
        .add_optional(
            "restore_file"s,
            &Arguments::restore_file,
            ""s,
            { "--restore"s },
            "Restore backup file to device"s)
        .build();
}

