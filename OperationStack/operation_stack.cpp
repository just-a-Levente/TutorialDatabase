//
// Created by lkovacs on 5/31/25.
//

#include "operation_stack.h"
#include "../Exceptions/exceptions.h"

OperationStack::OperationStack() {
    nextIndex = 0;
    operations.clear();
}

OperationStack::~OperationStack() {
    for (auto operation : operations)
        delete operation;
}

void OperationStack::recordOperation(Operation *newOperation) {
    for (int i = operations.size() - 1; i >= nextIndex; --i) {
        delete operations[i];
        operations.pop_back();
    }
    operations.push_back(newOperation);
    nextIndex++;
}

Operation * OperationStack::getRedoOperation() {
    if (nextIndex == operations.size())
        throw UndoRedoException("There's no operation to redo!");

    nextIndex++;
    return operations[nextIndex-1];
}

Operation * OperationStack::getUndoOperation() {
    if (nextIndex == 0)
        throw UndoRedoException("There's no operation to undo!");

    nextIndex--;
    return operations[nextIndex];
}
