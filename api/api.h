#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "api/file.h"
#include "api/master_block.h"
#include "either/either.h"

struct Success {};
struct MasterBlock;
struct File;

enum class APIFailureReason : uint8_t
{
    GeneralFailure,
    UnknownFailure,
    NotEnoughDiskSpace,
    FileNotFound,
    DeviceNotReady
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

