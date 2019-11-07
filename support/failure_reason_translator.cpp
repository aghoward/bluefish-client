#include "support/failure_reason_translator.h"

#include "api/api.h"

#include <string>

std::string FailureReasonTranslator::to_string(const FailureReason& failure_reason) const
{
    using namespace std::string_literals;

    if (failure_reason == FailureReason::GeneralFailure)
        return "General Failure"s;
    if (failure_reason == FailureReason::NotEnoughDiskSpace)
        return "Not enough disk space"s;
    if (failure_reason == FailureReason::FileNotFound)
        return "File not found"s;
    if (failure_reason == FailureReason::UnknownFailure)
        return "Unknown failure reason";
    return "Unimplemented error"s;
}
