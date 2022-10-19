#include "commands/read_file_command.h"

#include <string>

#include "commands/models/file.h"
#include "either/either.h"
#include "support/failure_reason_translator.h"

namespace models = bf::commands::models;

either<models::File, FailureReason> ReadFileCommand::execute(
        const std::string& filename,
        std::string&& master_password,
        const std::string& encryption_iv)
{
    auto encrypted_filename = _encrypter.encrypt(
        std::string(filename),
        std::string(master_password),
        encryption_iv);

    return _api.read_file(encrypted_filename)
        .map(
            [&] (const auto& file) -> models::File {
                return decrypt_file(file, std::move(master_password), encryption_iv);
            },
            [&] (const auto& api_failure_reason) -> FailureReason {
                return _failure_reason_translator.translate(api_failure_reason);
            });
}

models::File ReadFileCommand::decrypt_file(
        const File& file,
        std::string&& master_password,
        const std::string& encryption_iv)
{
    using namespace std::string_literals;

    auto filename = _decrypter.decrypt(
        file.name,
        std::string(master_password),
        encryption_iv)
        .match(
            [] (auto&& plaintext) { return plaintext; },
            [] (auto&&) { return ""s; });

    auto username = _decrypter.decrypt(
        file.username,
        std::string(master_password),
        encryption_iv)
        .match(
            [] (auto&& plaintext) { return plaintext; },
            [] (auto&&) { return ""s; });

    auto password = _decrypter.decrypt(
        file.password,
        std::move(master_password),
        encryption_iv)
        .match(
            [] (auto&& plaintext) { return plaintext; },
            [] (auto&&) { return ""s; });

    return models::File(std::move(filename), std::move(username), std::move(password));
}
