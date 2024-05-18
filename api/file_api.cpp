#include "api/file_api.h"
#include "api/api.h"
#include "api/serialization.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <stdexcept>

namespace bf {
    void FileAPI::save_to_file(const std::string& filepath) const
    {
        std::ofstream fd(filepath, std::ios::binary);
        if (!fd.is_open())
            throw std::runtime_error("Cannot open file: " + filepath);

        fd << _master_block;
        fd << _files.size();
        for (const auto& file : _files)
            fd << file;

        fd.close();
    }

    void FileAPI::load_from_file(const std::string& filepath)
    {
        std::uint16_t file_count;

        std::ifstream fd(filepath, std::ios::binary);
        if (!fd.is_open())
            throw std::runtime_error("Cannot open file: " + filepath);

        fd >> _master_block;
        fd >> file_count;
        _files = std::vector<File>(file_count);
        for (auto index = 0u; index < file_count && fd.good() && !fd.eof(); index++)
            fd >> _files[index];

        if (!fd.good() || (fd.eof() && _files.size() < file_count))
        {
            fd.close();
            throw std::runtime_error("Failed to load all files from: " + filepath);
        }

        fd.close();
    }

    either<Success, APIFailureReason> FileAPI::wait_ready()
    {
        return Success{};
    }

    either<Success, APIFailureReason> FileAPI::write_file(const File& file)
    {
        _files.push_back(file);
        save_to_file(_password_file_path);
        return Success{};
    }

    either<File, APIFailureReason> FileAPI::read_file(const std::string& filename)
    {
        auto it = std::find_if(_files.begin(), _files.end(), [&] (const auto& file) { return file.name == filename; });
        if (it == _files.end())
            return APIFailureReason::FileNotFound;
        return *it;
    }

    either<std::vector<std::string>, APIFailureReason> FileAPI::list_files()
    {
        std::vector<std::string> file_names(_files.size());
        std::transform(_files.begin(), _files.end(), file_names.begin(), [] (const auto& file) { return file.name; });
        return file_names;
    }

    either<Success, APIFailureReason> FileAPI::remove_file(const std::string& filename)
    {
        auto it = std::find_if(_files.begin(), _files.end(), [&] (const auto& file) { return file.name == filename; });
        if (it == _files.end())
            return APIFailureReason::FileNotFound;
        _files.erase(it);
        return Success{};
    }

    either<Success, APIFailureReason> FileAPI::format(const std::string& iv, const std::string& challenge)
    {
        _files = std::vector<File>();
        _master_block = MasterBlock();
        _master_block.file_count = 0u;
        _master_block.challenge = challenge;
        _master_block.encryption_iv = iv;
        _master_block.free_inodes = 0u;
        save_to_file(_password_file_path);
        return Success{};
    }

    either<MasterBlock, APIFailureReason> FileAPI::get_master_block()
    {
        return _master_block;
    }

}
