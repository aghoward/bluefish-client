#pragma once

#include "cdif/cdif.h"

class SupportModule : public cdif::IModule
{
    public:
        void load(cdif::Container&) override;
};
