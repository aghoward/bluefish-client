add_library(ui_console INTERFACE)
target_link_libraries(ui_console INTERFACE
    ui_console_commands
    ui_console_common
)

add_subdirectory(commands)
add_subdirectory(common)
