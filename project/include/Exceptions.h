#ifndef PROJECT_INCLUDE_EXCEPTIONS_H_
#define PROJECT_INCLUDE_EXCEPTIONS_H_

#include <exception>
#include <string>

class UnknownCommandException : public std::exception {
 public:
    explicit UnknownCommandException(const std::string& msg);
    const char* what() const noexcept;
 private:
    std::string message;
};

#endif  // PROJECT_INCLUDE_EXCEPTIONS_H_
