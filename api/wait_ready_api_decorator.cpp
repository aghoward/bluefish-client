#include "api/wait_ready_api_decorator.h"

#include "api/api.h"
#include "api/file.h"
#include "api/binary_api.h"
#include "api/serialization.h"
#include "either/either.h"

#include <string>
#include <vector>

either<Success, APIFailureReason> WaitReadyAPIDecorator::wait_ready()
{
    return _decorated.wait_ready();
}


either<Success, APIFailureReason> WaitReadyAPIDecorator::write_file(const File& file)
{
    return wait_ready()
        .foldFirst(
            [&] (const auto&) { return _decorated.write_file(file); }
        );
}

either<File, APIFailureReason> WaitReadyAPIDecorator::read_file(const std::string& filename)
{
    return wait_ready()
        .foldFirst(
            [&] (const auto&) { return _decorated.read_file(filename); }
        );
}

either<std::vector<std::string>, APIFailureReason> WaitReadyAPIDecorator::list_files()
{
    return wait_ready()
        .foldFirst(
            [&] (const auto&) { return _decorated.list_files(); }
        );
}

either<Success, APIFailureReason> WaitReadyAPIDecorator::remove_file(const std::string& filename)
{
    return wait_ready()
        .foldFirst(
            [&] (const auto&) { return _decorated.remove_file(filename); }
        );
}

either<Success, APIFailureReason> WaitReadyAPIDecorator::format(const std::string& iv, const std::string& challenge)
{
    return wait_ready()
        .foldFirst(
            [&] (const auto&) { return _decorated.format(iv, challenge); }
        );
}

either<MasterBlock, APIFailureReason> WaitReadyAPIDecorator::get_master_block()
{
    return wait_ready()
        .foldFirst(
            [&] (const auto&) { return _decorated.get_master_block(); }
        );
}
