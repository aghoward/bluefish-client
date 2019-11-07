#include "encryption/encryption.h"

#include "encryption/encryption_helpers.h"

#include <cryptopp/filters.h>
#include <cryptopp/twofish.h>
#include <cryptopp/eax.h>

#include <cstdint>
#include <string>
#include <vector>

std::string Encrypter::encrypt(
    std::string&& plaintext,
    std::string&& password,
    const std::string& iv) const
{
    using namespace std::string_literals;

    auto password_bytes = bytes_from(password, get_key_size(password));
    auto iv_bytes = bytes_from(iv, static_cast<uint32_t>(CryptoPP::Twofish::BLOCKSIZE));

    auto encryption = CryptoPP::EAX<CryptoPP::Twofish>::Encryption();
    encryption.SetKeyWithIV(password_bytes.data(), password_bytes.size(), iv_bytes.data());

    auto output = ""s;
    CryptoPP::StringSource(plaintext, true,
            new CryptoPP::AuthenticatedEncryptionFilter(encryption,
                new CryptoPP::StringSink(output)));

    clear_data(plaintext);
    clear_data(password);
    clear_data(password_bytes);

    return output;
}

std::string Decrypter::decrypt(
        const std::string& cyphertext,
        std::string&& password,
        const std::string& iv) const
{
    using namespace std::string_literals;

    auto password_bytes = bytes_from(password, get_key_size(password));
    auto iv_bytes = bytes_from(iv, static_cast<uint32_t>(CryptoPP::Twofish::BLOCKSIZE));

    auto decryption = CryptoPP::EAX<CryptoPP::Twofish>::Decryption();
    decryption.SetKeyWithIV(password_bytes.data(), password_bytes.size(), iv_bytes.data());

    auto output = ""s;
    CryptoPP::StringSource(cyphertext, true,
            new CryptoPP::AuthenticatedDecryptionFilter(decryption,
                new CryptoPP::StringSink(output)));

    clear_data(password);
    clear_data(password_bytes);

    return output;
}
