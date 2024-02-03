cmake_minimum_required(VERSION 3.12)

add_compile_options(-Wall -Wextra -pedantic -O3)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


project(bluefish-client)

add_executable(bluefish bluefish.cc)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/argparsing/include
    ${CMAKE_CURRENT_SOURCE_DIR}/cdif/include
    ${CMAKE_CURRENT_SOURCE_DIR}/either/include
)
target_link_libraries(bluefish PUBLIC
    serial
    ui
    ui_console
    ui_console_commands
    ui_console_common
    commands
    commands_common
    support
    api
    encryption
    cryptopp::cryptopp
)
target_compile_features(bluefish PRIVATE cxx_std_20)

add_subdirectory(cryptopp-cmake)
add_subdirectory(cdif)
add_subdirectory(either)
add_subdirectory(api)
add_subdirectory(argparsing)
add_subdirectory(commands)
add_subdirectory(encryption)
add_subdirectory(serial)
add_subdirectory(support)
add_subdirectory(ui)
