#pragma once

#include "api/api.h"
#include "api/file.h"
#include "api/master_block.h"
#include "either/either.h"
#include "serial/io_device.h"

#include <string>
#include <vector>

class WaitReadyAPIDecorator : public API
{
    private:
        API& _decorated;
        IODevice& _device;

    protected:
        either<Success, APIFailureReason> wait_ready() override;

    public:
        WaitReadyAPIDecorator(API& api, IODevice& device)
            : _decorated(api), _device(device)
        {}

        either<Success, APIFailureReason> write_file(const File&) override;
        either<File, APIFailureReason> read_file(const std::string&) override;
        either<std::vector<std::string>, APIFailureReason> list_files() override;
        either<Success, APIFailureReason> remove_file(const std::string&) override;
        either<Success, APIFailureReason> format(const std::string&, const std::string&) override;
        either<MasterBlock, APIFailureReason> get_master_block() override;
};
