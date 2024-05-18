#pragma once

#include "api/api.h"
#include "api/file.h"
#include "api/master_block.h"
#include "either/either.h"
#include <string>
#include <vector>

namespace bf {
    class FileAPI : public API
    {
        private:
            std::string _password_file_path;
            std::vector<File> _files;
            MasterBlock _master_block;

            void save_to_file(const std::string&) const;
            void load_from_file(const std::string&);

        public:
            FileAPI(const std::string& password_file_path)
                : _password_file_path(password_file_path),
                _files({}),
                _master_block()
            {
                load_from_file(_password_file_path);
            }

            either<Success, APIFailureReason> wait_ready();
            either<Success, APIFailureReason> write_file(const File&);
            either<File, APIFailureReason> read_file(const std::string&);
            either<std::vector<std::string>, APIFailureReason> list_files();
            either<Success, APIFailureReason> remove_file(const std::string&);
            either<Success, APIFailureReason> format(const std::string&, const std::string&);
            either<MasterBlock, APIFailureReason> get_master_block();
    };
}
