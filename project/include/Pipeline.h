#ifndef PROJECT_INCLUDE_PIPELINE_H_
#define PROJECT_INCLUDE_PIPELINE_H_

#include <string>
#include <memory>

#include "IOperation.h"
#include "Exceptions.h"

class Pipeline {
 public:
    void Execute();
    void Construct(const std::string& input);

 private:
    std::shared_ptr<IOperation> firstOperation;
    std::weak_ptr<IOperation> lastOperation;

    void InsertOperation(const std::shared_ptr<IOperation>& operation);
};


#endif  // PROJECT_INCLUDE_PIPELINE_H_
