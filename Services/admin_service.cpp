//
// Created by lkovacs on 3/26/25.
//

#include "admin_service.h"

AdminService::AdminService(Repository& tutorialDatabase, OperationStack& undoRedoStack) : tutorial_database(&tutorialDatabase), operationStack(&undoRedoStack) {}

AdminService::~AdminService() {
    this->tutorial_database = nullptr;
}

void AdminService::addTutorialToDatabase(const Tutorial &newTutorial) {
    Operation* addOp = new AddOperation(newTutorial);
    this->tutorial_database->addTutorial(newTutorial);
    operationStack->recordOperation(addOp);
}

void AdminService::removeTutorialFromDatabase(const Tutorial &tutorialToRemove) {
    Tutorial removeTutorial = findTutorialInDatabase(tutorialToRemove.getLink());
    Operation* removeOp = new RemoveOperation(removeTutorial);
    this->tutorial_database->removeTutorial(tutorialToRemove);
    operationStack->recordOperation(removeOp);
}

void AdminService::updateTutorialInDatabase(const Tutorial &updatedTutorial) {
    Tutorial oldTutorial = findTutorialInDatabase(updatedTutorial.getLink());
    Operation* updateOp = new UpdateOperation(oldTutorial, updatedTutorial);
    this->tutorial_database->updateTutorial(updatedTutorial);
    operationStack->recordOperation(updateOp);
}

void AdminService::undoOperation() {
    Operation* undoOp = operationStack->getUndoOperation();

    if (undoOp->getOperationType() == "add")
        tutorial_database->removeTutorial(undoOp->getUndoParameter());

    else if (undoOp->getOperationType() == "remove")
        tutorial_database->addTutorial(undoOp->getUndoParameter());

    else if (undoOp->getOperationType() == "update")
        tutorial_database->updateTutorial(undoOp->getUndoParameter());
}

void AdminService::redoOperation() {
    Operation* redoOp = operationStack->getRedoOperation();

    if (redoOp->getOperationType() == "add")
        tutorial_database->addTutorial(redoOp->getRedoParameter());

    else if (redoOp->getOperationType() == "remove")
        tutorial_database->removeTutorial(redoOp->getRedoParameter());

    else if (redoOp->getOperationType() == "update")
        tutorial_database->updateTutorial(redoOp->getRedoParameter());
}

vector<Tutorial> &AdminService::returnContentsOfDatabase() const {
    return this->tutorial_database->getVector();
}

Tutorial AdminService::findTutorialInDatabase(const string &link) const {
    return this->tutorial_database->findTutorial(link);
}
