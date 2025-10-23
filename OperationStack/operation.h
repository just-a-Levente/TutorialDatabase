//
// Created by lkovacs on 5/31/25.
//

#ifndef OPERATION_H
#define OPERATION_H

#include "../Domain/tutorial.h"
#include <string>
using std::string;

class Operation {

public:
    virtual ~Operation() = default;

    virtual string getOperationType() = 0;
    virtual Tutorial getRedoParameter() = 0;
    virtual Tutorial getUndoParameter() = 0;
};

class AddOperation final : public Operation {

    Tutorial addTutorialParameter;

public:
    explicit AddOperation(Tutorial tutorialToAdd) : addTutorialParameter(tutorialToAdd) {}

    string getOperationType() override { return "add"; }
    Tutorial getRedoParameter() override { return addTutorialParameter; }
    Tutorial getUndoParameter() override { return addTutorialParameter; }
};

class RemoveOperation final : public Operation {

    Tutorial removeTutorialParameter;

public:
    explicit RemoveOperation(Tutorial tutorialToRemove) : removeTutorialParameter(tutorialToRemove) {}

    string getOperationType() override { return "remove"; }
    Tutorial getRedoParameter() override { return removeTutorialParameter; }
    Tutorial getUndoParameter() override { return removeTutorialParameter; }
};

class UpdateOperation final : public Operation {

    Tutorial oldTutorialParameter;
    Tutorial newTutorialParameter;

public:
    explicit UpdateOperation(Tutorial oldTutorial, Tutorial newTutorial) : oldTutorialParameter(oldTutorial), newTutorialParameter(newTutorial) {}

    string getOperationType() override { return "update"; }
    Tutorial getRedoParameter() override { return newTutorialParameter; }
    Tutorial getUndoParameter() override { return oldTutorialParameter; }
};

#endif //OPERATION_H
