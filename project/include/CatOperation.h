#ifndef PROJECT_INCLUDE_CATOPERATION_H_
#define PROJECT_INCLUDE_CATOPERATION_H_

#include <fstream>
#include <string>
#include <memory>

#include "IOperation.h"

class CatOperation : public IOperation {
 public:
    CatOperation() = default;
    explicit CatOperation(std::istream& in);
    void ProcessLine(const std::string& str) override;
    void HandleEndOfInput() override;
    void SetNextOperation(const std::shared_ptr<IOperation>& _nextOperation) override;
 private:
    std::string data;
    std::shared_ptr<IOperation> nextOperation = nullptr;
};


#endif  // PROJECT_INCLUDE_CATOPERATION_H_
