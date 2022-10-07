#pragma once

#include <exception>
#include <string>
#include <Windows.h>

class Error : public std::exception {
private:
    std::string message;

public:
    Error(std::string msg) : message(msg) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(hConsole, 12);
        std::cerr << msg << "\n";
        SetConsoleTextAttribute(hConsole, 7);
    }
    std::string what() {
        return message;
    }
};