#pragma once

#include "api/api.h"
#include "api/master_block.h"
#include "encryption/encryption.h"
#include "support/failure_reason_translator.h"

class ListFilesCommand
{
    private:
        API& _api;
        FailureReasonTranslator& _failure_reason_translator;
        Decrypter& _decrypter;

        std::vector<std::string> list_files(
            const MasterBlock& master_block,
            std::string&& master_password,
            const std::vector<std::string>& encrypted_filenames);

    public:
        ListFilesCommand(API& api, FailureReasonTranslator& frt, Decrypter& dec)
            :
            _api(api),
            _failure_reason_translator(frt),
            _decrypter(dec)
        {}

        either<std::vector<std::string>, FailureReason> execute(
                const MasterBlock& master_block,
                std::string&& master_password);
};
