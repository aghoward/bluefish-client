#include <algorithm>
#include <string>
#include <vector>

#include "api/binary_api.h"
#include "api/file.h"
#include "api/identifiers.h"
#include "api/serialization.h"
#include "either/either.h"

#include <iostream>
#include <type_traits>

APIFailureReason convert_status(CommandStatus status)
{
    if (status == CommandStatus::Fail)
        return APIFailureReason::GeneralFailure;
    if (status == CommandStatus::NotEnoughDiskSpace)
        return APIFailureReason::NotEnoughDiskSpace;
    if (status == CommandStatus::FileNotFound)
        return APIFailureReason::FileNotFound;
    return APIFailureReason::UnknownFailure;
}

either<Success, APIFailureReason> BinaryAPI::wait_ready()
{
    CommandStatus status;
    _device >> status;
    if (status == CommandStatus::Ready)
        return Success{};
    return APIFailureReason::DeviceNotReady;
}

either<std::string, APIFailureReason> BinaryAPI::get_filename(const FileId& id)
{
    return wait_ready()
        .foldFirst(
            [&] (auto&&) -> either<std::string, APIFailureReason> {
                _device << Command::GetFileName << id;

                CommandStatus status;
                _device >> status;

                if (status != CommandStatus::OK)
                    return convert_status(status);

                std::string filename;
                _device >> filename;

                return filename;
            });
}

either<FileId, APIFailureReason> BinaryAPI::get_file_id(const std::string& filename)
{
    auto ids = list_ids();
    auto matching_id = std::find_if(
        ids.begin(),
        ids.end(),
        [&] (const auto& id)
        {
            return get_filename(id)
                .match(
                    [&] (const auto& name) -> bool { return name == filename; },
                    [] (auto&&) -> bool { return false; });
        });
    if (matching_id != ids.end())
        return *matching_id;
    return APIFailureReason::FileNotFound;
}

either<Success, APIFailureReason> BinaryAPI::write_file(const File& file)
{
    _device << Command::WriteFile << file;

    CommandStatus status;
    _device >> status;

    if (status == CommandStatus::OK)
        return Success{};

    return convert_status(status);
}

either<File, APIFailureReason> BinaryAPI::read_file(const std::string& filename)
{
    return get_file_id(filename)
        .foldFirst(
            [&] (const auto& id) -> either<File, APIFailureReason> {
                return wait_ready()
                    .foldFirst(
                        [&] (auto&&) -> either<File, APIFailureReason> {
                            _device << Command::ReadFile << id;

                            CommandStatus status;
                            _device >> status;

                            if (status != CommandStatus::OK)
                                return convert_status(status);

                            File file;
                            _device >> file;
                            return file;
                        });
            });
}

std::vector<FileId> BinaryAPI::list_ids()
{
    uint8_t size = 0u;
    _device << Command::ListFiles;
    _device >> size;

    auto output = std::vector<FileId>(size);
    for (auto i = 0u; i < size; i++)
        _device >> output[i];

    return output;
}

either<std::vector<std::string>, APIFailureReason> BinaryAPI::list_files()
{
    auto ids = list_ids();
    auto filenames = std::vector<std::string>();
    auto failure = APIFailureReason::UnknownFailure;
    for (auto& id : ids)
    {
        auto failed = get_filename(id)
            .match(
                [&] (auto&& filename) -> bool {
                    filenames.push_back(filename);
                    return false;
                },
                [&] (auto&& f) -> bool {
                    failure = f;
                    return true;
                }
            );
        if (failed)
            return failure;
    }

    return filenames;
}

either<Success, APIFailureReason> BinaryAPI::remove_file(const std::string& filename)
{
    return get_file_id(filename)
        .foldFirst(
            [&] (const auto& id) -> either<Success, APIFailureReason> {
                return wait_ready()
                    .foldFirst(
                        [&] (auto&&) -> either<Success, APIFailureReason> {
                            _device << Command::RemoveFile << id;
                            CommandStatus status;
                            _device >> status;

                            if (status != CommandStatus::OK)
                                return convert_status(status);

                            return Success{};
                        });
            });
}

either<Success, APIFailureReason> BinaryAPI::format(const std::string& iv, const std::string& challenge)
{
    _device << Command::Format << iv << challenge;
    CommandStatus status;
    _device >> status;

    if (status != CommandStatus::OK)
        return convert_status(status);
    return Success{};
}

either<MasterBlock, APIFailureReason> BinaryAPI::get_master_block()
{
    _device << Command::GetMasterBlock;
    auto master_block = MasterBlock();
    _device >> master_block;
    return master_block;
}
