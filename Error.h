#pragma once

#include <exception>
#include <string>
#include "Library.h"

class Error : public std::exception {
private:
    std::string message;

public:
    Error(std::string msg) : message(msg) {
        ChangeConsoleColor(12);
        std::cerr << msg << "\n";
        ChangeConsoleColor(7);
    }
    std::string what() {
        return message;
    }
};