#include "ui/console/common/output.h"

#include <string>

#include "support/failure_reason.h"

namespace bf::ui::console::common::detail {
    std::string to_string(const FailureReason& failure)
    {
        using namespace std::string_literals;

        if (failure == FailureReason::GeneralFailure)
            return "General failure"s;
        if (failure == FailureReason::UnknownFailure)
            return "Unknown failure reason";
        if (failure == FailureReason::NotEnoughDiskSpace)
            return "Not enough disk space"s;
        if (failure == FailureReason::FileNotFound)
            return "File not found"s;
        if (failure == FailureReason::DeviceNotReady)
            return "Device failed to respond appropriately"s;
        if (failure == FailureReason::InvalidPassword)
            return "Invalid password"s;
        return "Unimplemented error"s;
    }

    std::string to_string(const AddFileFailure& failure)
    {
        using namespace std::string_literals;

        if (failure == AddFileFailure::MissingUsername)
            return "Username not provided"s;
        if (failure == AddFileFailure::MissingPassword)
            return "Password not provided"s;
        if (failure == AddFileFailure::MissingMasterPassword)
            return "Master password not provided"s;
        if (failure == AddFileFailure::MissingFilename)
            return "Filename not provided"s;
        if (failure == AddFileFailure::MissingInitializationVector)
            return "Initialization vector not provided"s;
        return "Unimplemented error"s;
    }

    std::string to_string(const ChallengeFailure& failure)
    {
        using namespace std::string_literals;

        if (failure == ChallengeFailure::InvalidPassword)
            return "Invalid password"s;
        return "Unimplemented error"s;
    }

    std::string to_string(const CreateBackupFailure& failure)
    {
        using namespace std::string_literals;

        if (failure == CreateBackupFailure::CannotOpenFileFromDisk)
            return "Cannot open local file on disk"s;
        return "Unimplemented error"s;
    }

    std::string to_string(const FormatFailure& failure)
    {
        using namespace std::string_literals;

        if (failure == FormatFailure::PasswordsDoNotMatch)
            return "Passwords do not match"s;
        return "Unimplemented error"s;
    }

    std::string to_string(const RestoreBackupFailure& failure)
    {
        using namespace std::string_literals;

        if (failure == RestoreBackupFailure::CannotOpenFile)
            return "Cannot open local file on disk"s;
        if (failure == RestoreBackupFailure::BackupFileCorrupt)
            return "Backup file appears to be corrupt"s;
        return "Unimplemented error"s;
    }
}
