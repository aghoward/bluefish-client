#pragma once

#include "api/api.h"
#include "commands/models/file.h"
#include "either/either.h"
#include "encryption/encryption.h"
#include "support/failure_reason.h"
#include "support/failure_reason_translator.h"

class ReadFileCommand
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Encrypter& _encrypter;
        Decrypter& _decrypter;

        bf::commands::models::File decrypt_file(
            const File& file,
            std::string&& master_password,
            const std::string& encryption_iv);
    public:
        ReadFileCommand(
            API& api,
            FailureReasonTranslator& frt,
            Encrypter& enc,
            Decrypter& dec)
            :
            _api(api),
            _failure_reason_translator(frt),
            _encrypter(enc),
            _decrypter(dec)
            {}

        either<bf::commands::models::File, FailureReason> execute(
                const std::string& filename,
                std::string&& master_password,
                const std::string& encryption_iv);
};
