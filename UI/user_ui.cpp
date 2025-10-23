//
// Created by lkovacs on 4/10/25.
//

#include "user_ui.h"
#include <iostream>

#include "../Exceptions/exceptions.h"

using std::cin;
using std::cout;
using std::endl;

string UserUI::getPresenter() {
    string input_presenter;
    cout << "Input the presenter for the filter:\n>";
    getline(cin, input_presenter);
    return input_presenter;
}

void UserUI::addTutorialsToWatch() {
    const string filter_presenter = getPresenter();
    vector<Tutorial> filtered_tutorials;
    for (const auto& tutorial : this->user_serv->returnContentsOfDatabase())
        if (filter_presenter.empty() || tutorial.getPresenter() == filter_presenter)
            filtered_tutorials.push_back(tutorial);

    int quit_status = 0, i = 0;
    while (quit_status == 0) {
        const Tutorial& currently_displayed_tutorial = filtered_tutorials[i];
        cout << currently_displayed_tutorial
            << "Do you want to add this tutorial to the watch list? (y/n/q for quit selection)" << std::endl;

        std::string choice;
        getline(cin, choice);
        if (choice == "q") quit_status = 1;
        else if (choice == "y") {
            try {
                this->user_serv->addTutorialToWatchList(currently_displayed_tutorial);
                cout << "Tutorial added to watchlist successfully\n";
            } catch (TutorialWithSameLinkException const& excep) {
                cout << excep.what() << "\n";
            }
        }

        ++i;
        if (i == filtered_tutorials.size())
            i = 0;
    }
}

void UserUI::seeTutorialsOnWatchlist() {
    while (!this->user_serv->getWatchList().empty()) {
        const Tutorial next_tutorial = this->user_serv->getWatchList().front();
        cout << next_tutorial;
        string command = "firefox " + next_tutorial.getLink();
        system(command.c_str());

        string response;
        cout << "Do you want to give a like? (y/n)" << endl;
        getline(std::cin, response);
        if (response == "y")
            this->user_serv->incrementTutorialLinkCount(next_tutorial.getLink());
        cout << endl;

        this->user_serv->getWatchList().erase(this->user_serv->getWatchList().begin());
    }
}

void UserUI::printMainMenu() {
    cout << "========== MAIN MENU ==========" << endl
        << "1. Add tutorials to the watchlist" << endl
        << "2. See the tutorials in the watchlist" << endl
        << "3. See the watchlist" << endl
        << "4. Display the tutorial's file" << endl
        << "0. Exit" << endl << endl;
}

void UserUI::startUI() {
    int exit_status = 0;
    while (exit_status == 0) {
        printMainMenu();
        string choice;
        getline(cin, choice);
        cout << '\n';

        switch (choice[0]) {
            case '1':
                addTutorialsToWatch();
            break;
            case '2':
                seeTutorialsOnWatchlist();
            break;
            case '3':
                for (const auto& tutorial_to_watch : this->user_serv->getWatchList()) {
                    cout << tutorial_to_watch;
                }
                cout << "\n";
                break;
            case '4':
                this->user_serv->saveWatchList();
                break;
            case '0':
                exit_status = 1;
                break;
            default:
                cout << "Invalid menu choice\n\n";
                break;
        }
    }
}
