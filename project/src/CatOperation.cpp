#include "CatOperation.h"

#include <iostream>
#include <sstream>

void CatOperation::ProcessLine(const std::string &str) {
    if (nextOperation) {
        nextOperation->ProcessLine(str);
    } else {
        std::cout << str << std::endl;
    }
}

CatOperation::CatOperation(std::istream& in)
    : data(std::istreambuf_iterator<char>(in), {}) {}

void CatOperation::HandleEndOfInput() {
    std::string line;
    std::istringstream input(data);
    while (std::getline(input, line)) {
        if (nextOperation)
            nextOperation->ProcessLine(line);
        else
            std::cout << line << std::endl;
    }
    if (nextOperation)
        nextOperation->HandleEndOfInput();
}

void CatOperation::SetNextOperation(const std::shared_ptr<IOperation> &_nextOperation) {
    nextOperation = _nextOperation;
}
