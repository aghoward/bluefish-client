#include "encryption/encryption_module.h"

#include "cdif/cdif.h"
#include "encryption/encryption.h"

void EncryptionModule::load(cdif::Container& ctx)
{
    ctx.bind<Encrypter>().in<cdif::Scope::Singleton>().build();
    ctx.bind<Decrypter>().in<cdif::Scope::Singleton>().build();
}
