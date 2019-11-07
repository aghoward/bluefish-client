#pragma once

#include "cdif/cdif.h"

class EncryptionModule : public cdif::IModule
{
    public:
        void load(cdif::Container&) override;
};
