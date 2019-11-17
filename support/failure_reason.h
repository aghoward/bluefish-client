#pragma once

enum class FailureReason
{
    GeneralFailure,
    UnknownFailure,
    NotEnoughDiskSpace,
    FileNotFound,
    DeviceNotReady,
    InvalidPassword,
    PasswordsDoNotMatch
};
