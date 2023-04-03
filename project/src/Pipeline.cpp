//
// Created by Николай Степанов on 23.03.2023.
//

#include "Pipeline.h"
#include "CatOperation.h"
#include "EchoOperation.h"
#include "WcOperation.h"

#include <utility>
#include <sstream>
#include <iostream>

Pipeline::Pipeline(std::string input)
    : input(std::move(input)) {
    Parse();
}

void Pipeline::Parse() {
    std::istringstream in(input);
    std::string command;
    while (std::getline(in, command, '|')) {
        if (command[0] == ' ') {
            command = command.substr(1);
        }
        std::string name, arg;
        std::istringstream commandIn(command);
        commandIn >> name >> arg;
        if (name == "cat") {
            std::ifstream file(arg);
            auto catOperation = std::make_shared<CatOperation>(file);
            InsertOperation(catOperation);
        } else if (name == "echo") {
            auto echoOperation = std::make_shared<EchoOperation>(arg);
            InsertOperation(echoOperation);
        } else if (name == "wc" && arg == "-l") {
            auto wcOperation = std::make_shared<WcOperation>();
            InsertOperation(wcOperation);
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
