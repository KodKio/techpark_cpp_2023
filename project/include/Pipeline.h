#ifndef PROJECT_INCLUDE_PIPELINE_H_
#define PROJECT_INCLUDE_PIPELINE_H_

#include <string>
#include <memory>

#include "IOperation.h"
#include "Exceptions.h"

class Pipeline {
 public:
    Pipeline() = delete;
    explicit Pipeline(std::string input);
    void Execute();

 private:
    std::string input;
    std::shared_ptr<IOperation> firstOperation;
    std::weak_ptr<IOperation> lastOperation;

    void InsertOperation(const std::shared_ptr<IOperation>& operation);
    void Parse();
};


#endif  // PROJECT_INCLUDE_PIPELINE_H_
