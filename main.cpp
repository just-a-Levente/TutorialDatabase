//
// Created by lkovacs on 3/24/25.
//

#include <QtWidgets>
#include "GUI/mainGUI.h"
#include "GUI/adminGUI.h"

int main(int argc, char *argv[]) {

    /*
    std::cout << "Choose type of repository:\n"
            << "1) Text file repository\n"
            << "2) SQL repository\n\n";

    string choice;
    getline(std::cin, choice);
    Repository* main_repo;
    switch (choice[0]) {
        case '1': {
            main_repo = new Repository("data.txt");
            break;
        }
        case '2': {
            main_repo = new SQLRepository("data.txt");
            break;
        }
        default: {
            std::cout << "Invalid choice\n\n";
            return 1;
        }
    }

    std::cout << "Choose file type for watch list:\n"
            << "1) HTML\n"
            << "2) CSV\n\n";

    getline(std::cin, choice);
    UserService* main_user_service;
    switch (choice[0]) {
        case '1': {
            main_user_service = new UserService(*main_repo);
            break;
        }
        case '2': {
            main_user_service = new CSVUserService(*main_repo);
            break;
        }
        default: {
            std::cout << "Invalid choice\n\n";
            delete main_repo;
            return 1;
        }
    }

    auto* main_admin_service = new AdminService(*main_repo);
    auto* main_admin_ui = new UI(*main_admin_service);
    auto* main_user_ui = new UserUI(*main_user_service);

    bool exit_status = false;
    while (!exit_status) {
        std::cout << "Operation mode:\n"
              << "1) Admin mode\n"
              << "2) User mode\n"
              << "0) Exit\n\n";

        string menu_choice;
        getline(std::cin, menu_choice);
        switch (menu_choice[0]) {
            case '1':
                main_admin_ui->startUI();
                break;
            case '2':
                main_user_ui->startUI();
                break;
            case '0':
                exit_status = true;
                break;
            default:
                std::cout << "Invalid menu choice\n\n";
                break;
        }
    }

    delete main_repo;
    delete main_admin_service;
    delete main_user_service;
    delete main_admin_ui;
    delete main_user_ui;
    */

    QApplication a(argc, argv);
    MainGUI mainWindow{};
    mainWindow.show();
    return QApplication::exec();
}
