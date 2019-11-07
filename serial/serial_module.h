#pragma once

#include "cdif/cdif.h"

class SerialModule : public cdif::IModule
{
    public:
        void load(cdif::Container& container) override;
};

