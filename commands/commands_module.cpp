#include "commands/commands_module.h"

#include <memory>

#include "cdif/cdif.h"
#include "commands/add_file_command.h"
#include "commands/change_password_command.h"
#include "commands/change_username_command.h"
#include "commands/create_backup_command.h"
#include "commands/format_command.h"
#include "commands/list_files_command.h"
#include "commands/print_usage_command.h"
#include "commands/read_file_command.h"
#include "commands/remove_file_command.h"
#include "commands/rename_file_command.h"
#include "commands/restore_backup_command.h"
#include "commands/verify_backup_command.h"
#include "commands/verify_challenge_command.h"
#include "encryption/encryption.h"
#include "support/failure_reason_translator.h"

void CommandsModule::load(cdif::Container& container)
{
    container
        .bind<AddFileCommand, API&, FailureReasonTranslator&, Encrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<FormatCommand, API&, FailureReasonTranslator&, Encrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<ListFilesCommand, API&, FailureReasonTranslator&, Decrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<ReadFileCommand, API&, FailureReasonTranslator&, Encrypter&, Decrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<RemoveFileCommand, API&, FailureReasonTranslator&, Encrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<RenameFileCommand, API&, FailureReasonTranslator&, Encrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<PrintUsageCommand, API&, FailureReasonTranslator&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<CreateBackupCommand, API&, FailureReasonTranslator&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<RestoreBackupCommand, API&, FailureReasonTranslator&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<VerifyBackupCommand>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<ChangePasswordCommand, API&, FailureReasonTranslator&, Encrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<ChangeUsernameCommand, API&, FailureReasonTranslator&, Encrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
    container
        .bind<VerifyChallengeCommand, API&, Decrypter&>()
        .in<cdif::Scope::Singleton>()
        .build();
}
