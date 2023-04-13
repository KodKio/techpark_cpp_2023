#include "Exceptions.h"

UnknownCommandException::UnknownCommandException(const std::string &msg) {
    message = "Unknown command: " + msg;
}


const char* UnknownCommandException::what() const noexcept {
    return message.c_str();
}
