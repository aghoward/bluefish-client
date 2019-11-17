#include "api/serialization.h"

#include <string>

#include "serial/io_device.h"


IODevice& operator<<(IODevice& device, const std::string& data)
{
    device << static_cast<uint16_t>(data.size());
    device.writeString(data);
    return device;
}

IODevice& operator>>(IODevice& device, std::string& data)
{
    uint16_t size = 0u;
    device >> size;
    data = device.readString(size);
    return device;
}

IODevice& operator>>(IODevice& device, MasterBlock& master_block)
{
    device >> master_block.free_inodes;
    device >> master_block.file_count;
    device >> master_block.encryption_iv;
    device >> master_block.challenge;
    return device;
}
