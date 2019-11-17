#include "support/failure_reason_translator.h"

#include "api/api.h"
#include "support/failure_reason.h"
#include "encryption/encryption.h"

#include <string>

std::string FailureReasonTranslator::to_string(const FailureReason& failure_reason) const
{
    using namespace std::string_literals;

    if (failure_reason == FailureReason::GeneralFailure)
        return "General Failure"s;
    if (failure_reason == FailureReason::UnknownFailure)
        return "Unknown failure reason";
    if (failure_reason == FailureReason::NotEnoughDiskSpace)
        return "Not enough disk space"s;
    if (failure_reason == FailureReason::FileNotFound)
        return "File not found"s;
    if (failure_reason == FailureReason::DeviceNotReady)
        return "Device failed to respond appropriately"s;
    if (failure_reason == FailureReason::InvalidPassword)
        return "Invalid password"s;
    if (failure_reason == FailureReason::PasswordsDoNotMatch)
        return "Passwords do not match"s;
    return "Unimplemented error"s;
}

FailureReason FailureReasonTranslator::translate(const APIFailureReason& failure_reason) const
{
    if (failure_reason == APIFailureReason::GeneralFailure)
        return FailureReason::GeneralFailure;
    if (failure_reason == APIFailureReason::UnknownFailure)
        return FailureReason::UnknownFailure;
    if (failure_reason == APIFailureReason::NotEnoughDiskSpace)
        return FailureReason::NotEnoughDiskSpace;
    if (failure_reason == APIFailureReason::FileNotFound)
        return FailureReason::FileNotFound;
    if (failure_reason == APIFailureReason::DeviceNotReady)
        return FailureReason::DeviceNotReady;
    return FailureReason::UnknownFailure;
}

FailureReason FailureReasonTranslator::translate(const EncryptionFailureReason& failure_reason) const
{
    if (failure_reason == EncryptionFailureReason::InvalidPassword)
        return FailureReason::InvalidPassword;
    return FailureReason::UnknownFailure;
}
