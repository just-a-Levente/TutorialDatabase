//
// Created by lkovacs on 5/14/25.
//

#include "mainGUI.h"
#include "../Services/admin_service.h"
#include "../Services/user_service.h"
#include "adminGUI.h"
#include "userGUI.h"
#include "graphGUI.h"
#include "tableviewGUI.h"

MainGUI::MainGUI(QWidget *parent) : QWidget(parent) {
    mainRepo = new Repository("data.txt");
    mainOperationStack = new OperationStack();
    watchModel = new WatchListModel(mainWatchList);
    this->init();
    this->connectSignalsAndSlots();
}

MainGUI::~MainGUI() {
    delete mainRepo;
    delete mainOperationStack;
    delete watchModel;
}

void MainGUI::init() {
    this->setWindowTitle("Menu");
    const auto screen = QApplication::primaryScreen();
    auto rect = screen->geometry();
    int height = 80;
    int width = 150;
    this->setGeometry(rect.width()/2 + 250, rect.height()/2 + 100, width, height);
    QApplication::setFont(QFont("Verdana", 11));

    this->layout = new QVBoxLayout{};

    this->adminUIButton = new QPushButton{"Admin"};
    this->userUIButton = new QPushButton{"User"};
    this->HTMLChoice = new QRadioButton{"HTML"};
    this->HTMLChoice->setChecked(true);
    this->CSVChoice = new QRadioButton{"CSV"};
    this->graphUIButton = new QPushButton{"Graph"};
    showWatchListButton = new QPushButton{"Show watchlist"};

    layout->addWidget(this->adminUIButton);
    layout->addWidget(this->userUIButton);
    layout->addWidget(this->HTMLChoice);
    layout->addWidget(this->CSVChoice);
    layout->addWidget(this->graphUIButton);
    layout->addWidget(showWatchListButton);
    this->setLayout(layout);
}

void MainGUI::connectSignalsAndSlots() {
    connect(this->adminUIButton, &QPushButton::clicked, this, &MainGUI::initializeAdminWidget);
    connect(this->userUIButton, &QPushButton::clicked, this, &MainGUI::initializeUserWidget);
    connect(this->HTMLChoice, &QRadioButton::clicked, this, &MainGUI::handleHTML);
    connect(this->CSVChoice, &QRadioButton::clicked, this, &MainGUI::handleCSV);
    connect(this->graphUIButton, &QPushButton::clicked, this, &MainGUI::initializeGraphWidget);
    connect(showWatchListButton, &QPushButton::clicked, this, &MainGUI::initializeWatchListView);
}

void MainGUI::handleHTML() { this->isHTML = true; }

void MainGUI::handleCSV() { this->isHTML = false; }

void MainGUI::initializeAdminWidget() {
    auto adminServ = new AdminService(*this->mainRepo, *mainOperationStack);
    auto adminWindow = new AdminGUI{*adminServ, this};
    adminWindow->show();
    this->hide();
}

void MainGUI::initializeUserWidget() {
    UserService* userServ;

    if (this->isHTML)
        userServ = new UserService(*this->mainRepo, *watchModel);
    else
        userServ = new CSVUserService(*this->mainRepo, *watchModel);

    auto userWindow = new UserGUI{*userServ, *watchModel, this};
    userWindow->show();
    this->hide();
}

void MainGUI::initializeGraphWidget() {
    auto graphWindow = new GraphGUI{*mainRepo, this};
    graphWindow->show();
    this->hide();
}

void MainGUI::initializeWatchListView() {
    auto graphWindow = new ViewGUI{*watchModel, this};
    graphWindow->show();
    this->hide();
}
