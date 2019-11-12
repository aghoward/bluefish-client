#pragma once

#include <string>

#include "either/either.h"

enum class EncryptionFailureReason
{
    InvalidPassword
};

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

        either<std::string, EncryptionFailureReason> decrypt(
            const std::string& cyphertext,
            std::string&& password,
            const std::string& iv) const;

};
