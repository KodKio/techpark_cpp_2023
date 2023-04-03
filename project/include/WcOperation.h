#ifndef PROJECT_INCLUDE_WCOPERATION_H_
#define PROJECT_INCLUDE_WCOPERATION_H_

#include <string>
#include <memory>
#include <utility>

#include "IOperation.h"

class WcOperation : public IOperation {
 public:
    WcOperation() = default;
    void ProcessLine(const std::string& str) override;
    void HandleEndOfInput() override;
    void SetNextOperation(const std::shared_ptr<IOperation>& _nextOperation) override;
 private:
    std::shared_ptr<IOperation> nextOperation = nullptr;
    int counter = 0;
};


#endif  // PROJECT_INCLUDE_WCOPERATION_H_
