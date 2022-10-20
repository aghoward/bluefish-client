#pragma once

#include "api/api.h"
#include "encryption/encryption.h"
#include "support/failure_reason_translator.h"
#include "support/success.h"

class ChangeUsernameCommand
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Encrypter& _encrypter;

    public:
        ChangeUsernameCommand(
            API& api,
            FailureReasonTranslator& frt,
            Encrypter& enc)
            :
            _api(api),
            _failure_reason_translator(frt),
            _encrypter(enc)
        {}

        either<bf::Success, FailureReason> execute(
                const std::string& filename,
                std::string&& username,
                std::string&& master_password,
                const std::string& encryption_iv);
};
