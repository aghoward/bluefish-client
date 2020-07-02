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
            "help"s,
            &Arguments::print_help,
            false,
            { "-h"s, "--help"s },
            "Print this help message and exit"s)
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
            "filename"s,
            &Arguments::add_file,
            ""s,
            { "-a"s, "--add"s },
            "Add file to device storage"s)
        .add_optional(
            "username"s,
            &Arguments::username,
            ""s,
            { "-u"s, "--username"s },
            "Username for file to add. Use in conjuction with -a|--add"s)
        .add_optional(
            "filename"s,
            &Arguments::remove_file,
            ""s,
            { "--remove"s, "--rm"s },
            "Remove file from storage"s)
        .add_optional(
            "filename"s,
            &Arguments::read_file,
            ""s,
            { "-r"s, "--read"s },
            "Read a file from storage"s)
        .add_optional(
            "rename_from"s,
            &Arguments::rename_file,
            ""s,
            { "-A"s, "--rename"s },
            "Renames a file from `rename_from` to `rename_to`. Use in conjuction with -n|--new-file"s)
        .add_optional(
            "rename_to"s,
            &Arguments::new_file_name,
            ""s,
            { "-n"s, "--new-file"s },
            "New name for file being renamed. Use in conjuction with -A|--rename"s)
        .add_optional(
            "filename"s,
            &Arguments::change_username_file,
            ""s,
            { "-U"s, "--change-username"s },
            "Change username for given file. Use in conjuction with -u|--username"s)
        .add_optional(
            "filename"s,
            &Arguments::change_password_file,
            ""s,
            { "-P"s, "--change-password"s },
            "Change password for given file"s)
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
            "filename"s,
            &Arguments::backup_file,
            ""s,
            { "--backup"s },
            "Backup data from device to local filesystem"s)
        .add_optional(
            "filename"s,
            &Arguments::restore_file,
            ""s,
            { "--restore"s },
            "Restore backup file to device"s)
        .add_optional(
            "filename"s,
            &Arguments::verify,
            ""s,
            { "--verify"s },
            "Verify a backup file"s)
        .build();
}

