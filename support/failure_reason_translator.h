#pragma once

#include "api/api.h"
#include "encryption/encryption.h"

#include <string>

class FailureReasonTranslator
{
    public:
        std::string to_string(const FailureReason& failure_reason) const;
        std::string to_string(const EncryptionFailureReason& failure_reason) const;
};
