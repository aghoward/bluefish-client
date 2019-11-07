#include "encryption/encryption_helpers.h"

#include <cstdint>
#include <string>
#include <unistd.h>
#include <vector>

#include <cryptopp/osrng.h>
#include <cryptopp/twofish.h>

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
    auto it = iv_str.begin();
    for (auto c : iv)
        *it++ = c;

    return iv_str;
}
