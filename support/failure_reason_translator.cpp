#include "support/failure_reason_translator.h"

#include "api/api.h"
#include "encryption/encryption.h"

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

std::string FailureReasonTranslator::to_string(const EncryptionFailureReason& failure_reason) const
{
    using namespace std::string_literals;
    if (failure_reason == EncryptionFailureReason::InvalidPassword)
        return "Invalid password"s;
    return "Unimplemented error"s;
}
