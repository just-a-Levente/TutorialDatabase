//
// Created by lkovacs on 3/25/25.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "../Domain/tutorial.h"
#include <vector>

using std::vector;

class Repository {
protected:
    string fileName;
    vector<Tutorial> tutorials;

    virtual void saveTutorials() const;

    virtual void loadTutorials();

public:
    explicit Repository(const string& inputFileName);

    virtual ~Repository() = default;

    /**
     * Default constructor
     * @throws FileNotFoundException If a file with this name is not found
     */
    // explicit Repository(const string &inputFileName);

    /**
     * @return The number of tutorials stored in the database
     */
    [[nodiscard]] unsigned int getNumberOfTutorials() const;

    /**
     * @return Reference to the Database object's tutorials field
     */
    [[nodiscard]] vector<Tutorial>& getVector();

    /**
     * Adds a new Tutorial object to the database
     * @param new_tutorial The tutorial to be added
     * @throws TutorialWithSameLinkException If a tutorial with the same link already exists
     */
    void addTutorial(const Tutorial &new_tutorial);

    /**
     * Removes a Tutorial object from the database
     * @param tutorial_remove The tutorial to be removed
     * @throws TutorialNotFoundException If a tutorial with the given link doesn't exist
     */
    void removeTutorial(const Tutorial &tutorial_remove);

    /**
     * Updates a Tutorial object's information inside the database
     * @param updated_tutorial The tutorial with the same link as another one and new information
     * @throws TutorialNotFoundException If a tutorial with the given link doesn't exist
     */
    void updateTutorial(const Tutorial &updated_tutorial);

    Tutorial findTutorial(const string &tutorial_link_find);
};


class SQLRepository final : public Repository {
public:
    explicit SQLRepository(const string &inputFileName);

private:
    ~SQLRepository() override = default;

    void saveTutorials() const override;

    void loadTutorials() override;
};

#endif //REPOSITORY_H
