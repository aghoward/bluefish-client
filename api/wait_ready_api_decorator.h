#pragma once

#include "api/api.h"
#include "api/file.h"
#include "api/master_block.h"
#include "either/either.h"

#include <string>
#include <vector>

class WaitReadyAPIDecorator : public API
{
    private:
        API& _decorated;

    protected:
        either<Success, APIFailureReason> wait_ready() override;

    public:
        WaitReadyAPIDecorator(API& api)
            : _decorated(api)
        {}

        either<Success, APIFailureReason> write_file(const File&) override;
        either<File, APIFailureReason> read_file(const std::string&) override;
        either<std::vector<std::string>, APIFailureReason> list_files() override;
        either<Success, APIFailureReason> remove_file(const std::string&) override;
        either<Success, APIFailureReason> format(const std::string&, const std::string&) override;
        either<MasterBlock, APIFailureReason> get_master_block() override;
};
