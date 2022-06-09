#include "api/file.h"
#include "api/master_block.h"
#include "api/serialization.h"
#include "commands/models/backup_file_dto.h"
#include "either/either.h"
#include "support/failure_reason.h"

#include <fstream>
#include <cstdint>
#include <string>
#include <vector>

namespace bf {
    either<BackupFileDTO, FailureReason> read_backup_file(const std::string& filename)
    {
        using namespace bf;

        BackupFileDTO output;
        uint16_t fileCount, fileIndex;

        std::ifstream fd(filename, std::ios::binary);
        if (!fd.is_open())
            return FailureReason::CannotOpenFileFromDisk;

        fd >> output.master_block;
        fd >> fileCount;

        output.files = std::vector<File>(fileCount);
        for (fileIndex = 0u; fileIndex < fileCount && fd.good() && !fd.eof(); fileIndex++)
            fd >> output.files[fileIndex];

        if (!fd.good() || (fd.eof() && fileIndex < fileCount))
        {
            fd.close();
            return FailureReason::BackupFileCorrupt;
        }

        fd.close();
        return output;
    }
}
