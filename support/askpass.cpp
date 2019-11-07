#include "support/askpass.h"

#include <string>
#include <iostream>

// Taken and modified from https://stackoverflow.com/a/1455007
#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void toggle_tty_echo(bool enabled)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode );

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enabled )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}

std::string askpass(const std::string& prompt)
{
    auto password = std::string();

    std::cout << prompt;
    toggle_tty_echo(false);
    std::getline(std::cin, password);
    toggle_tty_echo(true);
    std::cout << std::endl;

    return password;
}
