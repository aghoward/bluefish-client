#include "commands/commands_module.h"

#include "cdif/cdif.h"
#include "commands/add_file_command.h"
#include "commands/command_composite.h"
#include "commands/command.h"
#include "commands/format_command.h"
#include "commands/list_files_command.h"
#include "commands/print_usage_command.h"
#include "commands/read_file_command.h"
#include "commands/remove_file_command.h"
#include "encryption/encryption.h"
#include "support/failure_reason_translator.h"

#include <memory>

void CommandsModule::load(cdif::Container& container)
{
    container
        .bind<AddFileCommand, API&, FailureReasonTranslator&, Encrypter&>()
        .build();
    container
        .bind<FormatCommand, API&, FailureReasonTranslator&>()
        .build();
    container
        .bind<ListFilesCommand, API&, FailureReasonTranslator&>()
        .build();
    container
        .bind<ReadFileCommand, API&, FailureReasonTranslator&, Decrypter&>()
        .build();
    container
        .bind<RemoveFileCommand, API&, FailureReasonTranslator&>()
        .build();
    container
        .bind<PrintUsageCommand, API&, FailureReasonTranslator&>()
        .build();

    container.bindList<std::unique_ptr<Command>,
            std::unique_ptr<FormatCommand>,
            std::unique_ptr<AddFileCommand>,
            std::unique_ptr<RemoveFileCommand>,
            std::unique_ptr<ReadFileCommand>,
            std::unique_ptr<ListFilesCommand>,
            std::unique_ptr<PrintUsageCommand>>()
        .build();

    container
        .bind<CommandComposite, std::vector<std::unique_ptr<Command>>>()
        .as<Command>()
        .build();
}
