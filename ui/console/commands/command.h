#pragma once

#include "support/arguments.h"

namespace bf::ui::console::commands {
    class Command {
        public:
            virtual ~Command() {}

            virtual void execute(const Arguments& args) = 0;
            virtual bool matches(const Arguments& args) = 0;
    };
}
