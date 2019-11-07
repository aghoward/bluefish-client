#pragma once

#include "api/api.h"
#include "commands/command.h"
#include "encryption/encryption.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"

class ReadFileCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Decrypter& _decrypter;

    public:
        ReadFileCommand(
            API& api,
            FailureReasonTranslator& frt,
            Decrypter& dec)
            :
            _api(api),
            _failure_reason_translator(frt),
            _decrypter(dec)
            {}

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};
