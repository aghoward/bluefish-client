#pragma once

#include "api/api.h"
#include "api/file.h"
#include "either/either.h"
#include "serial/io_device.h"

#include <string>
#include <vector>

class WaitReadyAPIDecorator : public API
{
    private:
        API& _decorated;
        IODevice& _device;

        either<Success, FailureReason> wait_ready();

    public:
        WaitReadyAPIDecorator(API& api, IODevice& device)
            : _decorated(api), _device(device)
        {}

        either<Success, FailureReason> write_file(const File&) override;
        either<File, FailureReason> read_file(const std::string&) override;
        either<std::vector<std::string>, FailureReason> list_files() override;
        either<Success, FailureReason> remove_file(const std::string&) override;
        either<Success, FailureReason> format(const std::string&) override;
        either<MasterBlock, FailureReason> get_master_block() override;
};
