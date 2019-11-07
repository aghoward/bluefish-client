#pragma once

#include <string>

struct Arguments
{
    std::string device;
    uint32_t baud;
    bool list;

    std::string add_file;
    std::string username;

    std::string remove_file;
    std::string read_file;
    bool format;
    bool print_usage;
};

