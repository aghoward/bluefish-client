#pragma once

#include <string>

#include "encryption/encryption_helpers.h"

namespace bf::commands::models {
    class File
    {
        public:
            std::string filename;
            std::string username;
            std::string password;

            File (std::string&& name, std::string&& user, std::string&& pass)
                : filename(name),
                  username(user),
                  password(pass)
            {}

            File() = delete;
            File(const File&) = delete;
            File& operator=(const File&) = delete;

            File(File&& other) = default;
            File& operator=(File&& other) = default;

            ~File()
            {
                clear_data(filename);
                clear_data(username);
                clear_data(password);
            }
    };
}
