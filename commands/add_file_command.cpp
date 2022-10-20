#include "commands/add_file_command.h"

#include <iostream>
#include <string>

#include "either/either.h"
#include "support/arguments.h"
#include "support/success.h"

either<bf::Success, AddFileFailure> AddFileCommand::execute(
        const std::string& filename,
        const std::string& username,
        std::string&& password,
        std::string&& master_password,
        const std::string& encryption_iv)
{
    using namespace std::string_literals;

    if (username == ""s)
        return AddFileFailure::MissingUsername;
    if (password == ""s)
        return AddFileFailure::MissingPassword;
    if (master_password == ""s)
        return AddFileFailure::MissingMasterPassword;
    if (filename == ""s)
        return AddFileFailure::MissingFilename;
    if (encryption_iv == ""s)
        return AddFileFailure::MissingInitializationVector;

    auto encrypted_filename = _encrypter.encrypt(
            std::string(filename),
            std::string(master_password),
            encryption_iv);
    auto encrypted_username = _encrypter.encrypt(
            std::string(username),
            std::string(master_password),
            encryption_iv);
    auto encrypted_password = _encrypter.encrypt(
            std::move(password),
            std::move(master_password),
            encryption_iv);
    return write_file(encrypted_filename, encrypted_username, encrypted_password);
}

either<bf::Success, AddFileFailure> AddFileCommand::write_file(
        const std::string& filename,
        const std::string& username,
        const std::string& password)
{
    return _api.write_file({ filename, username, password })
        .map(
            [] (const auto&) -> bf::Success { return {}; },
            [] (const auto& api_failure_reason) -> AddFileFailure {
                return AddFileFailure(api_failure_reason);
            });
}
