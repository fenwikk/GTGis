#include <exception>
#include <string>

class Error : public std::exception {
private:
    std::string message;

public:
    Error(std::string msg) : message(msg) {}
    std::string what() {
        return message;
    }
};