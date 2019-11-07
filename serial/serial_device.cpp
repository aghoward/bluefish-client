#include "serial_device.h"

#include <cstdint>
#include <string>
#include <algorithm>
#include <iostream>
#include <utility>

#include <boost/bind.hpp>

using namespace std;
using namespace boost;

bool SerialDevice::isOpen() const
{
    return port.is_open();
}

void SerialDevice::close()
{
    if(isOpen()==false) return;
    port.close();
}

void SerialDevice::write(const char *data, std::size_t size)
{
    asio::write(port,asio::buffer(data,size));
}

void SerialDevice::writeString(const std::string& s)
{
    write(s.c_str(), s.size());
}

void SerialDevice::read(char *data, std::size_t size)
{
    asio::read(port, asio::buffer(data, size), asio::transfer_at_least(size));
}

std::string SerialDevice::readString(std::size_t size)
{
    std::string result(size,'\0');
    read(&result[0],size);
    return result;
}

SerialDevice::~SerialDevice()
{
    if (isOpen())
        close();
}
