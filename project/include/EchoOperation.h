#ifndef PROJECT_INCLUDE_ECHOOPERATION_H_
#define PROJECT_INCLUDE_ECHOOPERATION_H_

#include <string>
#include <memory>

#include "IOperation.h"

class EchoOperation : public IOperation {
 public:
    EchoOperation() = default;
    explicit EchoOperation(std::string arg);
    void ProcessLine(const std::string& str) override {};
    void HandleEndOfInput() override;
    void SetNextOperation(const std::shared_ptr<IOperation>& _nextOperation) override;
 private:
    std::string arg;
    std::shared_ptr<IOperation> nextOperation = nullptr;
};


#endif  // PROJECT_INCLUDE_ECHOOPERATION_H_
