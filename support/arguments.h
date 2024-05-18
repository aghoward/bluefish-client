#pragma once

#include <string>

struct Arguments
{
    bool print_help;

    std::string device;
    uint32_t baud;
    bool list;

    std::string device_filename;

    std::string add_file;
    std::string username;

    std::string remove_file;
    std::string read_file;

    std::string rename_file;
    std::string new_file_name;
    std::string change_password_file;
    std::string change_username_file;

    bool format;
    bool print_usage;

    std::string backup_file;
    std::string restore_file;
    std::string verify;
};

