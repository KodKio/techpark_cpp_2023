#include <iostream>
#include <utility>
#include "EchoOperation.h"

EchoOperation::EchoOperation(std::string arg)
    : arg(std::move(arg)) {}

void EchoOperation::HandleEndOfInput() {
    if (!nextOperation) {
        std::cout << arg << std::endl;
    } else {
        nextOperation->ProcessLine(arg);
        nextOperation->HandleEndOfInput();
    }
}

void EchoOperation::SetNextOperation(const std::shared_ptr<IOperation> &_nextOperation) {
    nextOperation = _nextOperation;
}
