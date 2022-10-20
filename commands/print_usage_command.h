#pragma once

#include "api/api.h"
#include "api/master_block.h"
#include "either/either.h"
#include "support/failure_reason.h"
#include "support/failure_reason_translator.h"

class PrintUsageCommand
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;

    public:
        PrintUsageCommand(API& api, FailureReasonTranslator& frt)
            : _api(api), _failure_reason_translator(frt) {}

        either<MasterBlock, FailureReason> execute();
};
