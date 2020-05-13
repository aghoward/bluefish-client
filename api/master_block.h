#pragma once

#include "api/serialization.h"

#include <cstdint>
#include <string>
#include <iostream>

namespace bf {}

struct MasterBlock
{
    uint32_t free_inodes;
    uint32_t file_count;
    std::string encryption_iv;
    std::string challenge;
};

template <typename T>
T& operator>>(T& device, MasterBlock& block)
{
    using namespace bf;

    device >> block.free_inodes;
    device >> block.file_count;
    device >> block.encryption_iv;
    device >> block.challenge;
    return device;
}

template <typename T>
T& operator<<(T& device, const MasterBlock& block)
{
    using namespace bf;

    device << block.free_inodes;
    device << block.file_count;
    device << block.encryption_iv;
    device << block.challenge;
    return device;
}
