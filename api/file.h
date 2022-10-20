#pragma once

#include <string>

#include "api/serialization.h"

struct File
{
    std::string name;
    std::string username;
    std::string password;
};

template <typename T>
T& operator<<(T& device, const File& file)
{
    using namespace bf;
    device << file.name << file.username << file.password;
    return device;
}

template <typename T>
T& operator>>(T& device, File& file)
{
    using namespace bf;
    device >> file.name >> file.username >> file.password;
    return device;
}
