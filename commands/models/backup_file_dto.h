#pragma once

#include "api/master_block.h"
#include "api/file.h"

#include <vector>


struct BackupFileDTO {
    MasterBlock master_block;
    std::vector<File> files;
};
