#pragma once

#include <cstdint>
#include <iostream>
#include <string>

struct MasterBlock
{
    uint32_t free_inodes;
    uint32_t file_count;
    std::string encryption_iv;
    std::string challenge;
};
