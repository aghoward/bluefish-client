#pragma once

#include "support/arguments.h"

class Command
{
    public:
        virtual void execute(const Arguments& arguments) = 0;
        virtual bool matches(const Arguments& arguments) const = 0;
};
