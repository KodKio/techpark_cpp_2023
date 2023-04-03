#ifndef PROJECT_INCLUDE_IOPERATION_H_
#define PROJECT_INCLUDE_IOPERATION_H_

#include <string>
#include <memory>

class IOperation {
 public:
    virtual void ProcessLine(const std::string& str) = 0;
    virtual void HandleEndOfInput() = 0;
    virtual void SetNextOperation(const std::shared_ptr<IOperation>& _nextOperation) = 0;
    virtual ~IOperation() = default;
};


#endif  // PROJECT_INCLUDE_IOPERATION_H_
