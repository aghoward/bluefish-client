#pragma once

#include "api/api.h"
#include "support/failure_reason.h"
#include "encryption/encryption.h"

#include <string>

class FailureReasonTranslator
{
    public:
        std::string to_string(const FailureReason& failure_reason) const;
        FailureReason translate(const APIFailureReason& failure_reason) const;
        FailureReason translate(const EncryptionFailureReason& failure_reason) const;
};
