//
// Created by lkovacs on 5/31/25.
//

#ifndef OPERATION_STACK_H
#define OPERATION_STACK_H

#include "operation.h"
#include <vector>
using std::vector;

class OperationStack {
    vector<Operation*> operations;
    int nextIndex;

public:
    OperationStack();
    ~OperationStack();

    void recordOperation(Operation* newOperation);
    Operation* getRedoOperation();
    Operation* getUndoOperation();
};

#endif //OPERATION_STACK_H
