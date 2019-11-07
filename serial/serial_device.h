#pragma once

#include <cstdint>
#include <stdexcept>

#include <boost/utility.hpp>
#include <boost/asio.hpp>

#include "io_device.h"
#include "support/arguments.h"

class SerialDevice : public IODevice
{
public:
    SerialDevice(const SerialDevice&) = delete;
    SerialDevice& operator=(const SerialDevice&) = delete;

    SerialDevice(SerialDevice&&) = default;
    SerialDevice& operator=(SerialDevice&&) = default;
    ~SerialDevice();

    SerialDevice(Arguments& arguments)
        : device_name(arguments.device),
        baud_rate(arguments.baud),
        opt_parity(boost::asio::serial_port_base::parity::none),
        opt_csize(boost::asio::serial_port_base::character_size(8)),
        opt_flow(boost::asio::serial_port_base::flow_control::none),
        opt_stop(boost::asio::serial_port_base::stop_bits::one),
        io(),
        port(io, arguments.device)
    {
        if (!port.is_open())
            port.open(device_name);
        port.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
        port.set_option(opt_parity);
        port.set_option(opt_csize);
        port.set_option(opt_flow);
        port.set_option(opt_stop);
    }

    bool isOpen() const override;
    void close() override;
    void write(const char *data, size_t size) override;
    void writeString(const std::string& s) override;
    void read(char *data, std::size_t size) override;
    std::string readString(std::size_t size) override;

private:

    std::string device_name;
    std::uint32_t baud_rate;
    boost::asio::serial_port_base::parity opt_parity;
    boost::asio::serial_port_base::character_size opt_csize;
    boost::asio::serial_port_base::flow_control opt_flow;
    boost::asio::serial_port_base::stop_bits opt_stop;

    boost::asio::io_service io;
    boost::asio::serial_port port;
};
