#pragma once

#include "api/api.h"

#include <string>

class FailureReasonTranslator
{
    public:
        std::string to_string(const FailureReason& failure_reason) const;
};
