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

either<Success, FailureReason> BinaryAPI::wait_ready()
{
    CommandStatus status;
    _device >> status;
    if (status == CommandStatus::Ready)
        return Success{};
    return FailureReason::DeviceNotReady;
}

either<std::string, FailureReason> BinaryAPI::get_filename(const FileId& id)
{
    return wait_ready()
        .match(
            [&] (auto&&) -> either<std::string, FailureReason> {
                _device << Command::GetFileName << id;

                CommandStatus status;
                _device >> status;

                if (status != CommandStatus::OK)
                    return convert_status(status);

                std::string filename;
                _device >> filename;

                return filename;
            },
            [] (auto&& failure) -> either<std::string, FailureReason> {
                return failure;
            });
}

either<FileId, FailureReason> BinaryAPI::get_file_id(const std::string& filename)
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
    return FailureReason::FileNotFound;
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
    return get_file_id(filename)
        .match(
            [&] (const auto& id) -> either<File, FailureReason> {
                return wait_ready()
                    .match(
                        [&] (auto&&) -> either<File, FailureReason> {
                            _device << Command::ReadFile << id;

                            CommandStatus status;
                            _device >> status;

                            if (status != CommandStatus::OK)
                                return convert_status(status);

                            File file;
                            _device >> file;
                            return file;
                        },
                        [] (auto&& failure) -> either<File, FailureReason> {
                            return failure;
                        });
            },
            [](auto&& failure) -> either<File, FailureReason> { return failure; });
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

either<std::vector<std::string>, FailureReason> BinaryAPI::list_files()
{
    auto ids = list_ids();
    auto filenames = std::vector<std::string>();
    auto failure = FailureReason::UnknownFailure;
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

either<Success, FailureReason> BinaryAPI::remove_file(const std::string& filename)
{
    return get_file_id(filename)
        .match(
            [&] (const auto& id) -> either<Success, FailureReason> {
                return wait_ready()
                    .match(
                        [&] (auto&&) -> either<Success, FailureReason> {
                            _device << Command::RemoveFile << id;
                            CommandStatus status;
                            _device >> status;

                            if (status != CommandStatus::OK)
                                return convert_status(status);

                            return Success{};
                        },
                        [] (auto&& failure) -> either<Success, FailureReason> { return failure; });
            },
            [] (auto&& failure) -> either<Success, FailureReason> { return failure; });
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
