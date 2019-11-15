#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "api/file.h"
#include "either/either.h"

struct Success {};

enum class FailureReason : uint8_t
{
    GeneralFailure,
    UnknownFailure,
    NotEnoughDiskSpace,
    FileNotFound,
    DeviceNotReady
};

struct MasterBlock
{
    uint32_t free_inodes;
    uint32_t file_count;
    std::string encryption_iv;
};

class API
{
    public:
        virtual ~API() {}
        
        virtual either<Success, FailureReason> wait_ready() = 0;
        virtual either<Success, FailureReason> write_file(const File&) = 0;
        virtual either<File, FailureReason> read_file(const std::string&) = 0;
        virtual either<std::vector<std::string>, FailureReason> list_files() = 0;
        virtual either<Success, FailureReason> remove_file(const std::string&) = 0;
        virtual either<Success, FailureReason> format(const std::string&) = 0;
        virtual either<MasterBlock, FailureReason> get_master_block() = 0;
};

