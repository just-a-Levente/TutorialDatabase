//
// Created by lkovacs on 4/10/25.
//

#ifndef USER_UI_H
#define USER_UI_H

#include "../Services/user_service.h"
using std::string;

class UserUI {
    UserService* user_serv;

public:
    explicit UserUI(UserService& associated_user_service) : user_serv(&associated_user_service) {}

    string getPresenter();

    void addTutorialsToWatch();

    void seeTutorialsOnWatchlist();

    void printMainMenu();

    void startUI();
};

#endif //USER_UI_H
