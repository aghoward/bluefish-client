#include "commands/print_usage_command.h"

#include "api/master_block.h"
#include "either/either.h"
#include "support/failure_reason.h"

either<MasterBlock, FailureReason> PrintUsageCommand::execute()
{
    return _api.get_master_block()
        .mapSecond(
            [&] (const auto& api_failure_reason)
            {
                return _failure_reason_translator.translate(api_failure_reason);
            });
}
