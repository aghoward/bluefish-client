#pragma once

#include <string>

#include "api/file.h"
#include "commands/models/backup_file_dto.h"
#include "either/either.h"
#include "support/failure_reason.h"

namespace bf {
    either<BackupFileDTO, RestoreBackupFailure> read_backup_file(const std::string& filename);
}
