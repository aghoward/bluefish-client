#pragma once

enum class FailureReason
{
    BEGIN,

    GeneralFailure,
    UnknownFailure,
    NotEnoughDiskSpace,
    FileNotFound,
    DeviceNotReady,
    InvalidPassword,

    END
};

enum class AddFileFailure
{
    MissingUsername = static_cast<int>(FailureReason::END) + 1,
    MissingPassword,
    MissingMasterPassword,
    MissingFilename,
    MissingInitializationVector
};

enum class CreateBackupFailure {
    CannotOpenFileFromDisk = static_cast<int>(FailureReason::END) + 1,
};

enum class FormatFailure {
    PasswordsDoNotMatch = static_cast<int>(FailureReason::END) + 1,
};

enum class ChallengeFailure {
    InvalidPassword = static_cast<int>(FailureReason::END) + 1,
};

enum class RestoreBackupFailure {
    CannotOpenFile = static_cast<int>(FailureReason::END) + 1,
    BackupFileCorrupt,
};
