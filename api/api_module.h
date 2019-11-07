#pragma once

#include "cdif/cdif.h"

class APIModule : public cdif::IModule
{
    public:
        void load(cdif::Container& container) override;
};
