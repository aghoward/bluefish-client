#include "encryption/encryption_helpers.h"

#include <cstdint>
#include <string>
#include <unistd.h>
#include <vector>
#include <iostream>

#include <cryptopp/osrng.h>
#include <cryptopp/twofish.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/sha3.h>

uint32_t get_key_size(const std::string& password)
{
    auto min_length = static_cast<uint32_t>(CryptoPP::Twofish::MIN_KEYLENGTH);
    auto default_length = static_cast<uint32_t>(CryptoPP::Twofish::DEFAULT_KEYLENGTH);
    auto max_length = static_cast<uint32_t>(CryptoPP::Twofish::MAX_KEYLENGTH);
    return (password.size() > min_length) ?
        ((password.size() > default_length) ? max_length : default_length)
        : min_length;
}

std::vector<uint8_t> bytes_from(
        const std::string& original,
        uint32_t size)
{
    auto output = std::vector<uint8_t>(size, 0x0);
    memcpy(output.data(), original.c_str(), original.size());
    return output;
}

std::string create_random_iv()
{
    auto rng = CryptoPP::AutoSeededRandomPool();
    uint8_t iv[CryptoPP::Twofish::BLOCKSIZE];
    rng.GenerateBlock(iv, sizeof(iv));

    auto iv_str = std::string(static_cast<uint32_t>(CryptoPP::Twofish::BLOCKSIZE), 0x0);
    iv_str.assign(reinterpret_cast<char*>(iv), sizeof(iv));

    return iv_str;
}

std::string print_hex(const std::string& data)
{
    std::string hex_str = "";
    CryptoPP::StringSource(data, true,
            new CryptoPP::HexEncoder(new CryptoPP::StringSink(hex_str)));

    return hex_str;
}

std::string create_password_from(const std::string& original)
{
    CryptoPP::SHA3_256 hasher;
    auto digest = std::string(hasher.DigestSize(), static_cast<char>(0x0));

    hasher.Update(reinterpret_cast<const uint8_t*>(original.data()), original.size());
    hasher.Final(reinterpret_cast<uint8_t*>(&digest[0]));

    return digest;
}
