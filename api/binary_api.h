#pragma once

#include "api/api.h"
#include "api/file.h"
#include "api/identifiers.h"
#include "either/either.h"
#include "serial/io_device.h"

#include <string>

enum class Command : uint8_t
{
    Unknown = 0u,
    WriteFile,
    ReadFile,
    GetMasterBlock,
    ListFiles,
    RemoveFile,
    Format,
    GetFileName
};

enum class CommandStatus : uint8_t
{
    OK = 0u,
    Fail,
    NotEnoughDiskSpace,
    FileNotFound,
    Ready
};

class BinaryAPI : public API
{
    private:
        IODevice& _device;

        either<std::string, FailureReason> get_filename(const FileId& id);
        either<FileId, FailureReason> get_file_id(const std::string& filename);
        std::vector<FileId> list_ids();

    protected:
        either<Success, FailureReason> wait_ready() override;

    public:
        BinaryAPI(IODevice& device)
            : _device(device) {}
        ~BinaryAPI() {}
        either<Success, FailureReason> write_file(const File& file) override;
        either<File, FailureReason> read_file(const std::string& filename) override; 
        either<std::vector<std::string>, FailureReason> list_files() override;
        either<Success, FailureReason> remove_file(const std::string& filename) override;
        either<Success, FailureReason> format(const std::string& iv) override;
        either<MasterBlock, FailureReason> get_master_block() override;
};

