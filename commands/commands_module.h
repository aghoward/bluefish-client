#pragma once

#include "cdif/cdif.h"

class CommandsModule : public cdif::IModule
{
    public:
        void load(cdif::Container& container) override;
};
