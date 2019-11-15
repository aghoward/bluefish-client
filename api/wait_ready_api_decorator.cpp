#include "api/wait_ready_api_decorator.h"

#include "api/api.h"
#include "api/file.h"
#include "api/binary_api.h"
#include "api/serialization.h"
#include "either/either.h"

#include <string>
#include <vector>

either<Success, FailureReason> WaitReadyAPIDecorator::wait_ready()
{
    return _decorated.wait_ready();
}


either<Success, FailureReason> WaitReadyAPIDecorator::write_file(const File& file)
{
    return wait_ready()
        .match(
            [&] (const auto&) { return _decorated.write_file(file); },
            [] (auto&& failure) -> either<Success, FailureReason> { return failure; }
        );
}

either<File, FailureReason> WaitReadyAPIDecorator::read_file(const std::string& filename)
{
    return wait_ready()
        .match(
            [&] (const auto&) { return _decorated.read_file(filename); },
            [] (auto&& failure) -> either<File, FailureReason> { return failure; }
        );
}

either<std::vector<std::string>, FailureReason> WaitReadyAPIDecorator::list_files()
{
    return wait_ready()
        .match(
            [&] (const auto&) { return _decorated.list_files(); },
            [] (auto&& failure) -> either<std::vector<std::string>, FailureReason> { return failure; }
        );
}

either<Success, FailureReason> WaitReadyAPIDecorator::remove_file(const std::string& filename)
{
    return wait_ready()
        .match(
            [&] (const auto&) { return _decorated.remove_file(filename); },
            [] (auto&& failure) -> either<Success, FailureReason> { return failure; }
        );
}

either<Success, FailureReason> WaitReadyAPIDecorator::format(const std::string& iv)
{
    return wait_ready()
        .match(
            [&] (const auto&) { return _decorated.format(iv); },
            [] (auto&& failure) -> either<Success, FailureReason> { return failure; }
        );
}

either<MasterBlock, FailureReason> WaitReadyAPIDecorator::get_master_block()
{
    return wait_ready()
        .match(
            [&] (const auto&) { return _decorated.get_master_block(); },
            [] (auto&& failure) -> either<MasterBlock, FailureReason> { return failure; }
        );
}
