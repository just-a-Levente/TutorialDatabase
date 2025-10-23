//
// Created by lkovacs on 3/26/25.
//

#ifndef UI_H
#define UI_H

#include "../Services/admin_service.h"
using std::string;
typedef std::pair<unsigned int, unsigned int> t_duration;

class UI {
    AdminService* admin_serv;

public:
    explicit UI(AdminService& associated_admin_service);

    string getLink();

    string getTitle();

    string getPresenter();

    vector<string> getDuration();

    string getLikes();

    void addMenu();

    void removeMenu();

    void updateMenu();

    void displayMenu();

    void printMainMenu();

    void startUI();
};

#endif //UI_H
