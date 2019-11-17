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

        either<std::string, APIFailureReason> get_filename(const FileId& id);
        either<FileId, APIFailureReason> get_file_id(const std::string& filename);
        std::vector<FileId> list_ids();

    protected:
        either<Success, APIFailureReason> wait_ready() override;

    public:
        BinaryAPI(IODevice& device)
            : _device(device) {}
        ~BinaryAPI() {}
        either<Success, APIFailureReason> write_file(const File& file) override;
        either<File, APIFailureReason> read_file(const std::string& filename) override;
        either<std::vector<std::string>, APIFailureReason> list_files() override;
        either<Success, APIFailureReason> remove_file(const std::string& filename) override;
        either<Success, APIFailureReason> format(const std::string& iv, const std::string& challenge) override;
        either<MasterBlock, APIFailureReason> get_master_block() override;
};

