//
// Created by lkovacs on 3/26/25.
//

#ifndef ADMIN_SERVICE_H
#define ADMIN_SERVICE_H

#include "../Domain/tutorial.h"
#include "../Repository/repository.h"
#include "../OperationStack/operation_stack.h"

/** Class which acts as an interface for the underlying database and the UI*/
class AdminService {
    Repository *tutorial_database;
    OperationStack *operationStack;

    //Tutorial getTutorialFromDatabase(string link);

public:
    /**
     * Constructor for the AdminService entity
     * @param tutorialDatabase The database that the admin layer will use
     */
    explicit AdminService(Repository& tutorialDatabase, OperationStack& undoRedoStack);

    ~AdminService();

    /**
     * Adds a new tutorial to the database (or throws an error if a tutorial with the same link already exists)
     * @param newTutorial The new tutorial
     */
    void addTutorialToDatabase(const Tutorial &newTutorial);

    /**
     * Attempts to remove a Tutorial object with the specified link in the database (throws error otherwise)
     * @param tutorialToRemove The tutorial to be removed
     */
    void removeTutorialFromDatabase(const Tutorial &tutorialToRemove);

    /**
     * Attempts to update the information of a Tutorial object with the specified link in the database (throws error otherwise)
     * @param updatedTutorial The tutorial with updated information
     */
    void updateTutorialInDatabase(const Tutorial &updatedTutorial);

    void undoOperation();
    void redoOperation();

    /**
     * @return Reference to the database's contents
     */
    [[nodiscard]] vector<Tutorial> &returnContentsOfDatabase() const;

    [[nodiscard]] Tutorial findTutorialInDatabase(const string &link) const;

};

#endif //ADMIN_SERVICE_H
