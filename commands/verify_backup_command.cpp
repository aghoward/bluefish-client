#include "commands/verify_backup_command.h"

#include <string>

#include "commands/common/read_backup_file.h"
#include "commands/models/backup_file_dto.h"
#include "either/either.h"
#include "support/failure_reason.h"

either<BackupFileDTO, RestoreBackupFailure> VerifyBackupCommand::execute(const std::string& filename)
{
    return bf::read_backup_file(filename);
}
