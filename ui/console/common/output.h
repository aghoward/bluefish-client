#pragma once

#include <iostream>
#include <string>

#include "support/failure_reason.h"

namespace bf::ui::console::common {
    namespace detail {
        std::string to_string(const FailureReason& failure);
        std::string to_string(const AddFileFailure& failure);
        std::string to_string(const ChallengeFailure& failure);
        std::string to_string(const CreateBackupFailure& failure);
        std::string to_string(const FormatFailure& failure);
        std::string to_string(const RestoreBackupFailure& failure);
    }

    template <typename TFailure>
    void write_failure(const TFailure& failure)
    {
        auto message = (static_cast<int>(failure) <= static_cast<int>(FailureReason::END))
            ? detail::to_string(FailureReason(failure))
            : detail::to_string(failure);
        std::cout << message << std::endl;
    }
}
