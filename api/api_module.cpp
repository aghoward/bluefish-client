#include "api/api_module.h"

#include "api/api.h"
#include "api/binary_api.h"
#include "api/wait_ready_api_decorator.h"
#include "cdif/cdif.h"
#include "serial/io_device.h"

#include <memory>

void APIModule::load(cdif::Container& container)
{
    container
        .bind<BinaryAPI, IODevice&>()
        .named("BinaryAPI")
        .as<API>()
        .in<cdif::Scope::Singleton>()
        .build();

    container
        .bind<WaitReadyAPIDecorator, API&, IODevice&>()
        .withIndexedParameterFrom<0, API&>(
            [] (const auto& ctx) -> API& { return ctx.template resolve<API&>("BinaryAPI"); }
        )
        .as<API>()
        .in<cdif::Scope::Singleton>()
        .build();
}
