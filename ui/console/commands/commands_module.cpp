#include "ui/console/commands/commands_module.h"

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
#include "ui/console/commands/add_file_command.h"
#include "ui/console/commands/change_password_command.h"
#include "ui/console/commands/change_username_command.h"
#include "ui/console/commands/command_composite.h"
#include "ui/console/commands/create_backup_command.h"
#include "ui/console/commands/format_command.h"
#include "ui/console/commands/list_files_command.h"
#include "ui/console/commands/print_usage_command.h"
#include "ui/console/commands/read_file_command.h"
#include "ui/console/commands/remove_file_command.h"
#include "ui/console/commands/rename_file_command.h"
#include "ui/console/commands/restore_backup_command.h"
#include "ui/console/commands/verify_backup_command.h"
#include "ui/console/common/input.h"

namespace bf::ui::console::commands {
    void CommandsModule::load(cdif::Container& container)
    {
        container
            .bind<common::Input, VerifyChallengeCommand&>()
            .in<cdif::Scope::Singleton>()
            .build();

        container
            .bind<AddFileCommand, ::AddFileCommand&, common::Input&>()
            .build();
        container
            .bind<ChangePasswordCommand, ::ChangePasswordCommand&, common::Input&>()
            .build();
        container
            .bind<ChangeUsernameCommand, ::ChangeUsernameCommand&, common::Input&>()
            .build();
        container
            .bind<CreateBackupCommand, ::CreateBackupCommand&, common::Input&>()
            .build();
        container
            .bind<FormatCommand, ::FormatCommand&, common::Input&>()
            .build();
        container
            .bind<ListFilesCommand, ::ListFilesCommand&, common::Input&>()
            .build();
        container
            .bind<PrintUsageCommand, ::PrintUsageCommand&>()
            .build();
        container
            .bind<ReadFileCommand, ::ReadFileCommand&, common::Input&>()
            .build();
        container
            .bind<RemoveFileCommand, ::RemoveFileCommand&, common::Input&>()
            .build();
        container
            .bind<RenameFileCommand, ::RenameFileCommand&, common::Input&>()
            .build();
        container
            .bind<RestoreBackupCommand, ::RestoreBackupCommand&>()
            .build();
        container
            .bind<VerifyBackupCommand, ::VerifyBackupCommand&>()
            .build();

        container.bindList<
                std::unique_ptr<Command>,
                std::unique_ptr<AddFileCommand>,
                std::unique_ptr<ChangePasswordCommand>,
                std::unique_ptr<ChangeUsernameCommand>,
                std::unique_ptr<CreateBackupCommand>,
                std::unique_ptr<FormatCommand>,
                std::unique_ptr<ListFilesCommand>,
                std::unique_ptr<PrintUsageCommand>,
                std::unique_ptr<ReadFileCommand>,
                std::unique_ptr<RemoveFileCommand>,
                std::unique_ptr<RenameFileCommand>,
                std::unique_ptr<RestoreBackupCommand>,
                std::unique_ptr<VerifyBackupCommand>>()
            .build();

        container
            .bind<CommandComposite, std::vector<std::unique_ptr<Command>>>()
            .as<Command>()
            .build();
    }
}
