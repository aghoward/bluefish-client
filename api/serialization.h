#pragma once

#include <cstring>
#include <string>
#include <type_traits>

#include "serial/io_device.h"
#include "api/file.h"
#include "api/api.h"

#include <iostream>

namespace detail {
    template <typename T>
    void write_integral(IODevice& device, T data)
    {
        char buf[sizeof(T)];
        for (auto i = 0u; i < sizeof(T); i++)
            buf[i] = (data >> (i * 8)) & 0xFF;
        device.write(buf, sizeof(T));
    }

    template <typename T>
    T read_integral(IODevice& device)
    {
        T out;
        char buf[sizeof(T)];
        device.read(buf, sizeof(T));
        memcpy(&out, buf, sizeof(T));
        return out;
    }

}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>>
IODevice& operator<<(IODevice& device, T data)
{
    if constexpr (std::is_enum_v<T>)
        detail::write_integral(device, static_cast<std::underlying_type_t<T>>(data));
    else
        detail::write_integral(device, data);
    return device;
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>>
IODevice& operator>>(IODevice& device, T& out)
{
    if constexpr(std::is_enum_v<T>)
        out = static_cast<T>(detail::read_integral<std::underlying_type_t<T>>(device));
    else
        out = detail::read_integral<T>(device);
    return device;
}

IODevice& operator<<(IODevice& device, const std::string& data);
IODevice& operator>>(IODevice& device, std::string& data);

IODevice& operator>>(IODevice& device, MasterBlock& master_block);
