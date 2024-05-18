#include "api/api_module.h"

#include "api/api.h"
#include "api/binary_api.h"
#include "api/file_api.h"
#include "api/wait_ready_api_decorator.h"
#include "cdif/cdif.h"
#include "cdif/container.h"
#include "serial/io_device.h"
#include "support/arguments.h"


API& resolve_api(const cdif::Container& ctx)
{
    auto arguments = ctx.resolve<Arguments&>();
    if (arguments.device_filename != "")
        return ctx.resolve<API&>("FileAPI");
    return ctx.resolve<API&>("BinaryAPI");
}

void APIModule::load(cdif::Container& container)
{
    container
        .bind<BinaryAPI, IODevice&>()
        .named("BinaryAPI")
        .as<API>()
        .in<cdif::Scope::Singleton>()
        .build();

    container
        .bind<bf::FileAPI, std::string>()
        .withIndexedParameterFrom<0, std::string>(
            [] (const auto& ctx) { return ctx.template resolve<Arguments&>().device_filename; }
        )
        .named("FileAPI")
        .as<API>()
        .in<cdif::Scope::Singleton>()
        .build();

    container
        .bind<WaitReadyAPIDecorator, API&>()
        .withIndexedParameterFrom<0, API&>(&resolve_api)
        .as<API>()
        .in<cdif::Scope::Singleton>()
        .build();
}
