#pragma once

#include "api/api.h"
#include "commands/command.h"
#include "either/either.h"
#include "encryption/encryption.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"
#include "support/failure_reason.h"

class FormatCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Encrypter& _encrypter;

        either<std::string, FailureReason> get_master_password() const;
        std::string encrypt_challenge(
            std::string&& challenge,
            std::string&& password,
            const std::string& iv) const;

    public:
        FormatCommand(API& api, FailureReasonTranslator& frt, Encrypter& enc)
            :
            _api(api),
            _failure_reason_translator(frt),
            _encrypter(enc)
        {}

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};
