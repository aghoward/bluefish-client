add_library(commands STATIC
    add_file_command.cpp
    change_password_command.cpp
    change_username_command.cpp
    commands_module.cpp
    create_backup_command.cpp
    format_command.cpp
    list_files_command.cpp
    print_usage_command.cpp
    read_file_command.cpp
    remove_file_command.cpp
    rename_file_command.cpp
    restore_backup_command.cpp
    verify_backup_command.cpp
    verify_challenge_command.cpp
)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/common
)

target_link_libraries(commands PUBLIC
    commands_common
)
