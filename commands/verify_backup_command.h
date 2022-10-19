#pragma once

#include <string>

#include "commands/models/backup_file_dto.h"
#include "either/either.h"
#include "support/failure_reason.h"

class VerifyBackupCommand
{
    public:
        VerifyBackupCommand()
        {}

        either<BackupFileDTO, RestoreBackupFailure> execute(const std::string& filename);
};

