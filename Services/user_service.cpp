//
// Created by lkovacs on 4/9/25.
//

#include "user_service.h"
#include "../Exceptions/exceptions.h"
#include <algorithm>
#include <fstream>
#include <cstring>

vector<Tutorial> &UserService::returnContentsOfDatabase() const {
    return this->tutorial_database->getVector();
}

vector<Tutorial> & UserService::getWatchList() const {
    return this->watchList.getWatchList();
}

vector<Tutorial> UserService::filterThroughPresenter(const string& presenter) const {
    vector<Tutorial> filteredTutorials;
    for (const auto& tutorial : this->tutorial_database->getVector())
        if (tutorial.getPresenter() == presenter || presenter.empty())
            filteredTutorials.push_back(tutorial);
    return filteredTutorials;
}

void UserService::addTutorialToWatchList(const Tutorial& preferred_tutorial) {
    auto pos = std::find(this->watchList.getWatchList().begin(), this->watchList.getWatchList().end(), preferred_tutorial);
    if (pos != this->watchList.getWatchList().end())
        throw TutorialWithSameLinkException("The tutorial already exists in the watchlist!\n");
    this->watchList.addNewItem(preferred_tutorial);
}

void UserService::incrementTutorialLinkCount(const string &link) const {
    Tutorial liked_tutorial = this->tutorial_database->findTutorial(link);

    const unsigned int update_like_count = liked_tutorial.getLikes() + 1;
    liked_tutorial.setLikes(update_like_count);
    this->tutorial_database->updateTutorial(liked_tutorial);
}

UserService::UserService(Repository &tutorialDatabase, WatchListModel& watchListModel) : tutorial_database(&tutorialDatabase), watchList(watchListModel) {}

void UserService::saveWatchList() {
    std::ofstream html_file("watchlist.html");
    html_file << "<!DOCTYPE html>\n"
              << "<html>\n"
              << "<head>\n"
              << "    <title>Playlist</title>"
              << "</head>\n"
              << "<body>\n"
              << "<table border=\"1\">\n";

    for (const auto &tutorial: this->watchList.getWatchList()) {
        html_file << "    <tr>\n"
                  << "        <td>" << tutorial.getLink() << "</td>\n"
                  << "        <td>" << tutorial.getTitle() << "</td>\n"
                  << "        <td>" << tutorial.getPresenter() << "</td>\n"
                  << "        <td>" << tutorial.getDuration().first << ":" << tutorial.getDuration().second << "</td>\n"
                  << "        <td>" << tutorial.getLikes() << "</td>\n"
                  << "    </tr>\n";
    }

    html_file << "</table>\n"
              << "</body>\n"
              << "</html>\n";

    html_file.close();
    system("firefox watchlist.html");
}

UserService::~UserService() { this->tutorial_database = nullptr; }


CSVUserService::CSVUserService(Repository &tutorialDatabase, WatchListModel& watchList) : UserService(tutorialDatabase, watchList) {}

CSVUserService::~CSVUserService() { this->tutorial_database = nullptr; }

void CSVUserService::saveWatchList() {
    std::ofstream csv_file("watchlist.csv");
    for (const auto &tutorial: this->watchList.getWatchList()) {
        csv_file << tutorial;
    }
    csv_file.close();
    system("libreoffice watchlist.csv");
}
