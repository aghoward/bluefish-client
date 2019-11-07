#pragma once

#include <string>

class Encrypter
{
    public:
        Encrypter() {}

        std::string encrypt(
            std::string&& plaintext,
            std::string&& password,
            const std::string& iv) const;

};

class Decrypter
{
    public:
        Decrypter() {}

        std::string decrypt(
            const std::string& cyphertext,
            std::string&& password,
            const std::string& iv) const;

};
