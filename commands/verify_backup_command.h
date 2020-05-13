#pragma once

#include "commands/command.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"

class VerifyBackupCommand : public Command
{
    private:
        FailureReasonTranslator& _failure_reason_translator;

    public:
        explicit VerifyBackupCommand(FailureReasonTranslator& frt)
            : _failure_reason_translator(frt)
        {}

        bool matches(const Arguments& args) const override;
        void execute(const Arguments& args) override;
};

