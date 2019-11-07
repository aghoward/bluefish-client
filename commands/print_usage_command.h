#pragma once

#include "api/api.h"
#include "commands/command.h"
#include "support/arguments.h"
#include "support/failure_reason_translator.h"

class PrintUsageCommand : public Command
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;

    public:
        PrintUsageCommand(API& api, FailureReasonTranslator& frt)
            : _api(api), _failure_reason_translator(frt) {}

        void execute(const Arguments& arguments) override;
        bool matches(const Arguments& arguments) const override;
};
