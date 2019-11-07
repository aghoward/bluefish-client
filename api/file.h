#pragma once

#include <string>

#include "serial/io_device.h"

struct File
{
    std::string name;
    std::string username;
    std::string password;
};

IODevice& operator<<(IODevice&, const File&);
IODevice& operator>>(IODevice&, File&);
