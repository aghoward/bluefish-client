#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "api/file.h"
#include "either/either.h"

struct Success {};

enum class APIFailureReason : uint8_t
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
    std::string challenge;
};

class API
{
    public:
        virtual ~API() {}
        
        virtual either<Success, APIFailureReason> wait_ready() = 0;
        virtual either<Success, APIFailureReason> write_file(const File&) = 0;
        virtual either<File, APIFailureReason> read_file(const std::string&) = 0;
        virtual either<std::vector<std::string>, APIFailureReason> list_files() = 0;
        virtual either<Success, APIFailureReason> remove_file(const std::string&) = 0;
        virtual either<Success, APIFailureReason> format(const std::string&, const std::string&) = 0;
        virtual either<MasterBlock, APIFailureReason> get_master_block() = 0;
};

