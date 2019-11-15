#pragma once

#include <cstdint>

#include "serial/io_device.h"
#include "api/serialization.h"

enum class IdentifierType
{
    File
};

template <IdentifierType T>
class Identifier
{
    public:
        uint16_t value;

        Identifier()
            : value(0u) {}

        explicit Identifier(uint16_t id)
            : value(id) {}
};

template <IdentifierType T>
IODevice& operator<<(IODevice& stream, const Identifier<T>& id)
{
    return stream << id.value;
}

template <IdentifierType T>
IODevice& operator>>(IODevice& stream, Identifier<T>& id)
{
    return stream >> id.value;
}

typedef Identifier<IdentifierType::File> FileId;
