#pragma once

#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

uint32_t get_key_size(const std::string& password);
std::vector<uint8_t> bytes_from(const std::string&, uint32_t size);
std::string create_random_iv();

template <typename T>
void clear_data(T& input)
{
    for (auto& b : input)
        b = static_cast<std::remove_reference_t<decltype(b)>>(0);
}
