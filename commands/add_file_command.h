#pragma once

#include "api/api.h"
#include "commands/command.h"
#include "encryption/encryption.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"

class AddFileCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Encrypter& _encrypter;

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

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};