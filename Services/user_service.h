//
// Created by lkovacs on 4/9/25.
//

#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "../Domain/tutorial.h"
#include "../Repository/repository.h"
#include "../watchlistmodel.h"

class UserService {
protected:
    Repository *tutorial_database;
    WatchListModel watchList;

public:
    explicit UserService(Repository& tutorialDatabase, WatchListModel& watchListModel);

    virtual void saveWatchList();

    virtual ~UserService();

    /**
     * @return Reference to the database's vector
     */
    [[nodiscard]] vector<Tutorial> &returnContentsOfDatabase() const;

    /**
     * @return Reference to the UserService's watchlist
     */
    vector<Tutorial> &getWatchList() const;

    /**
     * Gets all the tutorials with a specific presenter (or all of them, if no presenter is passed as parameter)
     * @param presenter The name of the presenter by which the tutorials are filtered
     * @return A vector containing the Tutorial objects after the filtering
     */
    [[nodiscard]] vector<Tutorial> filterThroughPresenter(const string& presenter) const;

    /**
     * Inserts a new Tutorial object into the watchlist
     * @param preferred_tutorial The Tutorial object the user adds to their watchlist
     * @throws TutorialWithSameLinkException A tutorial with the same link already is in the watchlist
     */
    void addTutorialToWatchList(const Tutorial& preferred_tutorial);

    /**
     * Update the like count of the tutorial the user watches by adding one
     * @param link The link of the liked tutorial
     * @throws TutorialNotFoundException No tutorial with the specified link exists inside the watchlist
     */
    void incrementTutorialLinkCount(const string& link) const;

};


class CSVUserService final : public UserService {
public:
    explicit CSVUserService(Repository& tutorialDatabase,  WatchListModel& watchListReference);

private:
    ~CSVUserService() override;

    void saveWatchList() override;

};


#endif //USER_SERVICE_H
