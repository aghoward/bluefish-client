#include "serial/serial_module.h"

#include "cdif/cdif.h"
#include "serial/io_device.h"
#include "serial/serial_device.h"
#include "support/arguments.h"

void SerialModule::load(cdif::Container& container)
{
    container
        .bind<SerialDevice, Arguments&>()
        .as<IODevice>()
        .in<cdif::Scope::Singleton>()
        .build();
}
