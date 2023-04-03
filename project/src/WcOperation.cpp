#include <iostream>
#include "WcOperation.h"

void WcOperation::ProcessLine(const std::string &str) {
    counter++;
}

void WcOperation::HandleEndOfInput() {
    if (nextOperation) {
        nextOperation->ProcessLine(std::to_string(counter));
        nextOperation->HandleEndOfInput();
    } else {
        std::cout << counter << std::endl;
    }
    counter = 0;
}

void WcOperation::SetNextOperation(const std::shared_ptr<IOperation> &_nextOperation) {
    nextOperation = _nextOperation;
}
