#pragma once

#include <cstdint>
#include <string>
#include <vector>

class IODevice
{
    public:
        virtual void close() = 0;
        virtual bool isOpen() const = 0;
        virtual void write(const char *data, size_t size) = 0;
        virtual void writeString(const std::string& s) = 0;
        virtual void read(char *data, std::size_t size) = 0;
        virtual std::string readString(std::size_t size) = 0;
};
