#pragma once

#include <string>

void toggle_tty_echo(bool enabled);
std::string askpass(const std::string& prompt = "Password: ");
