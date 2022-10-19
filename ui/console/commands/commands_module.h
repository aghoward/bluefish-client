#pragma once

#include "cdif/cdif.h"

namespace bf::ui::console::commands {
    class CommandsModule : public cdif::IModule
    {
        public:
            void load(cdif::Container& container) override;
    };
}
