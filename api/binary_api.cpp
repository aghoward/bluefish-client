#include <string>
#include <vector>

#include "api/binary_api.h"
#include "api/file.h"
#include "api/serialization.h"
#include "either/either.h"

#include <iostream>
#include <type_traits>

FailureReason convert_status(CommandStatus status)
{
    if (status == CommandStatus::Fail)
        return FailureReason::GeneralFailure;
    if (status == CommandStatus::NotEnoughDiskSpace)
        return FailureReason::NotEnoughDiskSpace;
    if (status == CommandStatus::FileNotFound)
        return FailureReason::FileNotFound;
    return FailureReason::UnknownFailure;
}

either<Success, FailureReason> BinaryAPI::write_file(const File& file)
{
    _device << Command::WriteFile << file;

    CommandStatus status;
    _device >> status;

    if (status == CommandStatus::OK)
        return Success{};

    return convert_status(status);
}

either<File, FailureReason> BinaryAPI::read_file(const std::string& filename)
{
    _device << Command::ReadFile << filename;

    CommandStatus status;
    _device >> status;

    if (status != CommandStatus::OK)
        return convert_status(status);

    File file;
    _device >> file;
    return file;
}

either<std::vector<std::string>, FailureReason> BinaryAPI::list_files()
{
    uint8_t size = 0u;
    _device << Command::ListFiles;
    _device >> size;

    auto output = std::vector<std::string>(size);
    for (auto i = 0u; i < size; i++)
        _device >> output[i];

    return output;
}

either<Success, FailureReason> BinaryAPI::remove_file(const std::string& filename)
{
    _device << Command::RemoveFile << filename;
    CommandStatus status;
    _device >> status;

    if (status != CommandStatus::OK)
        return convert_status(status);

    return Success{};
}

either<Success, FailureReason> BinaryAPI::format(const std::string& iv)
{
    _device << Command::Format << iv;
    CommandStatus status;
    _device >> status;

    if (status != CommandStatus::OK)
        return convert_status(status);
    return Success{};
}

either<MasterBlock, FailureReason> BinaryAPI::get_master_block()
{
    _device << Command::GetMasterBlock;
    auto master_block = MasterBlock();
    _device >> master_block;
    return master_block;
}
