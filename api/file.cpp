
#include "api/file.h"
#include "api/serialization.h"
#include "serial/io_device.h"

IODevice& operator<<(IODevice& device, const File& file)
{
    device << file.name << file.username << file.password;
    return device;
}

IODevice& operator>>(IODevice& device, File& file)
{
    device >> file.name >> file.username >> file.password;
    return device;
}
