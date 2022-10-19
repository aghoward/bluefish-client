#pragma once

#include "api/api.h"
#include "encryption/encryption.h"
#include "support/arguments.h"
#include "support/failure_reason.h"
#include "support/failure_reason_translator.h"
#include "support/success.h"

class AddFileCommand
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Encrypter& _encrypter;

        either<bf::Success, AddFileFailure> write_file(
            const std::string& filename,
            const std::string& username,
            const std::string& password);
    public:
        AddFileCommand(
            API& api,
            FailureReasonTranslator& frt,
            Encrypter& enc)
            :
            _api(api),
            _failure_reason_translator(frt),
            _encrypter(enc)
        {}

        either<bf::Success, AddFileFailure> execute(
                const std::string& filename,
                const std::string& username,
                std::string&& password,
                std::string&& master_password,
                const std::string& encryption_iv);
};
