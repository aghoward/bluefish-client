#pragma once

#include <cstring>
#include <iostream>
#include <string>
#include <type_traits>

#include "api/api.h"
#include "api/file.h"
#include "api/master_block.h"
#include "serial/io_device.h"

namespace detail {
    template <typename TDevice, typename T>
    void write_integral(TDevice& device, T data)
    {
        char buf[sizeof(T)];
        for (auto i = 0u; i < sizeof(T); i++)
            buf[i] = (data >> (i * 8)) & 0xFF;
        device.write(buf, sizeof(T));
    }

    template <typename TDevice, typename T>
    T read_integral(TDevice& device)
    {
        T out;
        char buf[sizeof(T)];
        device.read(buf, sizeof(T));
        memcpy(&out, buf, sizeof(T));
        return out;
    }

    template <typename T>
    struct remove_cvref
    {
        typedef std::remove_cv_t<std::remove_reference_t<T>> type;
    };

    template <typename T>
    using remove_cvref_t = typename remove_cvref<T>::type;
}

namespace bf {
    template <typename TDevice, typename T, typename = std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>>
    TDevice& operator<<(TDevice& device, T data)
    {
        if constexpr (std::is_enum_v<T>)
            detail::write_integral(device, static_cast<std::underlying_type_t<T>>(data));
        else
            detail::write_integral(device, data);
        return device;
    }

    template <typename TDevice, typename T, typename = std::enable_if_t<std::is_integral_v<T> || std::is_enum_v<T>>>
    TDevice& operator>>(TDevice& device, T& out)
    {
        if constexpr(std::is_enum_v<T>)
            out = static_cast<T>(detail::read_integral<TDevice, std::underlying_type_t<T>>(device));
        else
            out = detail::read_integral<TDevice, T>(device);
        return device;
    }

    template <
        typename TDevice,
        typename = std::enable_if_t<
            !std::is_same_v<
                detail::remove_cvref_t<TDevice>,
                detail::remove_cvref_t<decltype(std::cout)>
            >
        >
    >
    TDevice& operator<<(TDevice& device, const std::string& data)
    {
        bf::operator<<(device, static_cast<uint16_t>(data.size()));
        device.write(data.c_str(), data.size());
        return device;
    }

    template <typename TDevice>
    TDevice& operator>>(TDevice& device, std::string& data)
    {
        uint16_t size = 0u;

        bf::operator>>(device, size);
        std::string result(size,'\0');
        device.read(&result[0], size);

        data = result;
        return device;
    }


    template <typename T>
    T& operator>>(T& device, MasterBlock& block)
    {
        device >> block.free_inodes;
        device >> block.file_count;
        device >> block.encryption_iv;
        device >> block.challenge;
        return device;
    }

    template <typename T>
    T& operator<<(T& device, const MasterBlock& block)
    {
        device << block.free_inodes;
        device << block.file_count;
        device << block.encryption_iv;
        device << block.challenge;
        return device;
    }

    template <typename T>
    T& operator<<(T& device, const File& file)
    {
        device << file.name << file.username << file.password;
        return device;
    }

    template <typename T>
    T& operator>>(T& device, File& file)
    {
        device >> file.name >> file.username >> file.password;
        return device;
    }
}
