#pragma once

#include "api/file.h"
#include "commands/models/backup_file_dto.h"
#include "either/either.h"
#include "support/failure_reason.h"

#include <string>

namespace bf {
    either<BackupFileDTO, FailureReason> read_backup_file(const std::string& filename);
}
