#include "Pipeline.h"
#include "CatOperation.h"
#include "EchoOperation.h"
#include "WcOperation.h"

#include <sstream>
#include <iostream>

#define CAT_OPERATION_NAME "cat"
#define ECHO_OPERATION_NAME "echo"
#define WC_OPERATION_NAME "wc"
#define WC_PARAM_NAME "-l"

void Pipeline::Construct(const std::string& input) {
    std::istringstream in(input);
    std::string command;

    while (std::getline(in, command, '|')) {
        if (command[0] == ' ') {
            command = command.substr(1);
        }

        std::string name, arg;
        std::istringstream commandIn(command);
        commandIn >> name >> arg;

        if (name == CAT_OPERATION_NAME) {
            std::ifstream file(arg);
            InsertOperation(std::make_shared<CatOperation>(file));
        } else if (name == ECHO_OPERATION_NAME) {
            InsertOperation(std::make_shared<EchoOperation>(arg));
        } else if (name == WC_OPERATION_NAME && arg == WC_PARAM_NAME) {
            InsertOperation(std::make_shared<WcOperation>());
        } else {
           throw UnknownCommandException(name + " " + arg);
        }
    }
}

void Pipeline::InsertOperation(const std::shared_ptr<IOperation> &operation) {
    if (firstOperation == nullptr) {
        firstOperation = operation;
    } else {
        lastOperation.lock()->SetNextOperation(operation);
    }
    lastOperation = operation;
}

void Pipeline::Execute() {
    firstOperation->HandleEndOfInput();
}
