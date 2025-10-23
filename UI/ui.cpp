//
// Created by lkovacs on 3/26/25.
//

#include "ui.h"
#include "../Validator/TutorialValidator.h"
#include <iostream>
#include <vector>

#include "../Exceptions/exceptions.h"

#define cout std::cout
#define cin std::cin

string UI::getLink() {
    string input_link;
    cout << "Input the link:\n>";
    getline(cin, input_link);
    return input_link;
}

string UI::getTitle() {
    string input_title;
    cout << "Input the title:\n>";
    getline(cin, input_title);
    return input_title;
}

string UI::getPresenter() {
    string input_presenter;
    cout << "Input the presenter:\n>";
    getline(cin, input_presenter);
    return input_presenter;
}

vector<string> UI::getDuration() {
    string input_minutes, input_seconds;

    cout << "Input the number of minutes:\n>";
    getline(cin, input_minutes);

    cout << "Input the number of seconds:\n>";
    getline(cin, input_seconds);

    return {input_minutes, input_seconds};
}

string UI::getLikes() {
    string input_likes;
    cout << "Input the number of likes it already has:\n>";
    getline(cin, input_likes);
    return input_likes;
}

void UI::addMenu() {
    string new_link = getLink();
    string new_title = getTitle();
    string new_presenter = getPresenter();
    vector<string> new_duration = getDuration();
    string new_likes = "0";
    cout << "Do you want to input number of likes also? (y/n)\n>";
    string choice;
    getline(cin, choice);
    if (choice == "y")
        new_likes = getLikes();
    cout << '\n';

    try {
        TutorialValidator::validateDataPoints({new_link, new_title, new_presenter, new_duration[0], new_duration[1], new_likes});
    } catch (TutorialValidationException const& excep) {
        cout << excep.what() << "\n";
        return;
    }

    const t_duration new_duration_pair{std::stoul(new_duration[0]), std::stoul(new_duration[1])};
    const unsigned int new_number_of_likes = std::stoul(new_likes);

    try {
        const Tutorial newTutorial(new_link, new_title, new_presenter, new_duration_pair, new_number_of_likes);
        this->admin_serv->addTutorialToDatabase(newTutorial);
    } catch (TutorialWithSameLinkException const& excep) {
        cout << excep.what() << "\n";
        return;
    }
    cout << "Tutorial added successfully\n\n";
}

void UI::removeMenu() {
    const string remove_link_key = getLink();
    const Tutorial dummyTutorialToRemove(remove_link_key, "", "", t_duration{0, 0});
    try {
        this->admin_serv->removeTutorialFromDatabase(dummyTutorialToRemove);
    } catch (TutorialNotFoundException const& excep) {
        cout << excep.what() << "\n";
        return;
    }

    cout << "Tutorial removed successfully\n\n";
}

void UI::updateMenu() {
    cout << "=========== UPDATE MENU ===========\n"
            << "1. Update tutorial's title\n"
            << "2. Update tutorial's presenter\n"
            << "3. Update tutorial's duration\n"
            << "4. Update tutorial's number of likes\n\n>";
    string choice;
    getline(cin, choice);
    cout << "\n";

    string link_to_update = getLink();
    Tutorial tutorial_to_update;

    try {
        tutorial_to_update = this->admin_serv->findTutorialInDatabase(link_to_update);
    } catch (TutorialNotFoundException const& excep) {
        cout << excep.what() << "\n";
        return;
    }

    switch (choice[0]) {
        case '1': {
            const string add_title = getTitle();
            tutorial_to_update.setTitle(add_title);
            try {
                admin_serv->updateTutorialInDatabase(tutorial_to_update);
                cout << "Tutorial's title updated successfully\n\n";
            } catch (TutorialNotFoundException const& excep) {
                cout << excep.what() << "\n";
            }
            break;
        }
        case '2': {
            const string add_presenter = getPresenter();
            tutorial_to_update.setPresenter(add_presenter);
            try {
                admin_serv->updateTutorialInDatabase(tutorial_to_update);
                cout << "Tutorial's presenter updated successfully\n\n";
            } catch (TutorialNotFoundException const& excep) {
                cout << excep.what() << "\n";
            }
            break;
        }
        case '3': {
            const vector<string> input_duration = getDuration();

            try {
                TutorialValidator::validateDuration(input_duration);
            } catch (InvalidDurationException const& excep) {
                cout << excep.what() << "\n";
                break;
            }

            t_duration add_duration{std::stoull(input_duration[0]), std::stoull(input_duration[1])};
            tutorial_to_update.setDuration(add_duration);
            try {
                admin_serv->updateTutorialInDatabase(tutorial_to_update);
                cout << "Tutorial's duration updated successfully\n\n";
            } catch (TutorialNotFoundException const& excep) {
                cout << excep.what() << "\n";
            }
            break;
        }
        case '4': {
            const string input_likes = getLikes();

            try {
                TutorialValidator::validateUnsignedInt(input_likes);
            } catch (UnsignedIntNotFoundException const& excep) {
                cout << excep.what() << "\n";
                break;
            }

            const unsigned int add_number_of_likes = std::stoull(input_likes);
            tutorial_to_update.setLikes(add_number_of_likes);
            try {
                admin_serv->updateTutorialInDatabase(tutorial_to_update);
                cout << "Tutorial's number of likes updated successfully\n\n";
            } catch (TutorialNotFoundException const& excep) {
                cout << excep.what() << "\n";
            }
            break;
        }
        default: {
            cout << "Invalid menu choice\n\n";
            break;
        }
    }
}

void UI::displayMenu() {
    const vector<Tutorial> all_tutorials = this->admin_serv->returnContentsOfDatabase();
    for (const auto& tutorial : all_tutorials) {
        cout << tutorial;
    }
    if (all_tutorials.empty()) cout << "No tutorials in database\n\n";
    else cout << "\n";
}

void UI::printMainMenu() {
    cout << "=========== MAIN MENU ===========\n"
            << "1. Add a new tutorial to the database\n"
            << "2. Remove a tutorial from the database\n"
            << "3. Update a tutorial's information in the database\n"
            << "4. See all the tutorials from the database\n"
            << "0. Exit the program\n\n>";
}

void UI::startUI() {
    int exit_status = 0;
    while (exit_status == 0) {
        printMainMenu();
        string choice;
        getline(cin, choice);
        cout << '\n';

        switch (choice[0]) {
            case '1':
                addMenu();
                break;
            case '2':
                removeMenu();
                break;
            case '3':
                updateMenu();
                break;
            case '4':
                displayMenu();
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

UI::UI(AdminService& associated_admin_service) : admin_serv(&associated_admin_service) {}
