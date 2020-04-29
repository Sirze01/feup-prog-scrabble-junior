#include "../common/ConsoleSetup.h"
#include "../common/StringProcess.h"
#include <iostream>

bool setupConsole() {
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    // Set output mode to handle virtual terminal sequences
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE || hOut == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD dwOriginalInMode = 0;
    DWORD dwOriginalOutMode = 0;
    if (!GetConsoleMode(hIn, &dwOriginalInMode)) {
        return false;
    }
    if (!GetConsoleMode(hOut, &dwOriginalOutMode)) {
        return false;
    }
    DWORD dwInMode = dwOriginalInMode | ENABLE_VIRTUAL_TERMINAL_INPUT;
    if (!SetConsoleMode(hIn, dwInMode))
    {
        // Failed to set VT input mode, can't do anything here.
        return false;
    }
    DWORD dwOutMode = dwOriginalOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    if (!SetConsoleMode(hOut, dwOutMode)) {
        // we failed to set both modes, try to step down mode gracefully.
        dwOutMode = dwOriginalOutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwOutMode))
        {
            // Failed to set any VT mode, can't do anything here.
            return false;
        }
    }
#endif
    return true;
}

void clearConsole() {
    std::cout << "\x1B[2J\x1B[H";
}

void print(std::string message, const int foreColor, const int backColor) {
    std::cout << "\x1b[" << backColor << ";" << foreColor << "m" << message << "\x1b[" << ALL_DEFAULTS << "m";
}

void print(std::string message, int foreColor) {
    std::cout << "\x1b[" << foreColor << "m" << message << "\x1b[" << ALL_DEFAULTS << "m";
}

void print(const char c, const int foreColor, const int backColor) {
    std::cout << "\x1b[" << backColor << ";" << foreColor << "m" << c << "\x1b[" << ALL_DEFAULTS << "m";
}

void print(const char c, const int foreColor) {
    std::cout << "\x1b[" << foreColor << "m" << c << "\x1b[" << ALL_DEFAULTS << "m";
}