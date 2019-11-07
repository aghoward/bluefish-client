#include "support/support_module.h"

#include "cdif/cdif.h"
#include "support/failure_reason_translator.h"
#include "support/arguments.h"

void SupportModule::load(cdif::Container& container)
{
    container
        .bind<FailureReasonTranslator>()
        .in<cdif::Scope::Singleton>()
        .build();

    container
        .bind<Arguments>()
        .in<cdif::Scope::Singleton>()
        .build();
}
