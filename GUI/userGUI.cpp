//
// Created by lkovacs on 5/15/25.
//

#include "userGUI.h"

#include "exceptions.h"

UserGUI::UserGUI(UserService &ctrl, WatchListModel& model, QWidget *parent) : QWidget(parent, Qt::Window), controller(ctrl), model(model) {
    filteredTutorials = vector<Tutorial>{};
    position = -1;
    this->init();
    this->connectSignalsAndSlots();
    this->setAttribute(Qt::WA_DeleteOnClose);
}

UserGUI::~UserGUI() {
    this->parentWidget()->show();
    delete &controller;
}

void UserGUI::init() {
    this->setWindowTitle("Tutorial Watch List - User");

    // main widget (this)
    mainLayout = new QVBoxLayout{this};
    filterButton = new QPushButton{"Filter"};
    inputWidget = new QWidget;
    filterResult = new QLabel;
    filterResult->setAlignment(Qt::AlignCenter);
    iterButtonWidget = new QWidget;
    errorLabel = new QLabel{"Tutorial is already in the watchlist!"};
    errorLabel->setAlignment(Qt::AlignCenter);
    addButton = new QPushButton{"Add to watchlist"};
    stopFilterButton = new QPushButton{"Clear filter"};
    watchListView = new QTableView;
    watchListView->setModel(&model);
    displayFileButton = new QPushButton{"Display watchlist in file"};
    playWatchListButton = new QPushButton{"Play watchlist"};
    playWatchListWidget = new QWidget;
    mainLayout->addWidget(inputWidget);
    mainLayout->addWidget(filterButton);
    mainLayout->addWidget(filterResult);
    mainLayout->addWidget(iterButtonWidget);
    mainLayout->addWidget(errorLabel);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(stopFilterButton);
    mainLayout->addWidget(watchListView);
    mainLayout->addWidget(displayFileButton);
    mainLayout->addWidget(playWatchListButton);
    mainLayout->addWidget(playWatchListWidget);

    // inputWidget
    inputLayout = new QFormLayout{inputWidget};
    filterPresenterLabel = new QLabel{"&Filter by presenter:"};
    filterPresenterField = new QLineEdit;
    filterPresenterLabel->setBuddy(filterPresenterField);
    inputLayout->addRow(filterPresenterLabel, filterPresenterField);

    // iterButtonWidget
    iterButtonLayout = new QHBoxLayout{iterButtonWidget};
    goBackButton = new QPushButton{"<"};
    counterLabel = new QLabel;
    counterLabel->setAlignment(Qt::AlignCenter);
    goForwardButton = new QPushButton{">"};
    iterButtonLayout->addWidget(goBackButton);
    iterButtonLayout->addWidget(counterLabel);
    iterButtonLayout->addWidget(goForwardButton);

    // playWatchListWidget
    playWatchListLayout = new QVBoxLayout{playWatchListWidget};
    playingTutorialLabel = new QLabel;
    playingTutorialLabel->setAlignment(Qt::AlignCenter);
    playButtonsWidget = new QWidget;
    playWatchListLayout->addWidget(playingTutorialLabel);
    playWatchListLayout->addWidget(playButtonsWidget);

    // playButtonsWidget
    playButtonsLayout = new QHBoxLayout{playButtonsWidget};
    likeButton = new QPushButton{"Like"};
    nextButton = new QPushButton{"Next"};
    playButtonsLayout->addWidget(likeButton);
    playButtonsLayout->addWidget(nextButton);

    // Hiding some of the widgets at start up
    filterResult->hide();
    iterButtonWidget->hide();
    errorLabel->hide();
    addButton->hide();
    stopFilterButton->hide();
    if (controller.getWatchList().size() < 1)
        playWatchListButton->hide();
    playWatchListWidget->hide();
}

void UserGUI::connectSignalsAndSlots() {
    connect(filterButton, &QPushButton::clicked, this, &UserGUI::handleFilterResult);
    connect(goBackButton, &QPushButton::clicked, this, &UserGUI::handleGoBackwards);
    connect(goForwardButton, &QPushButton::clicked, this, &UserGUI::handleGoForward);
    connect(addButton, &QPushButton::clicked, this, &UserGUI::handleAddTutorialToWatchlist);
    connect(stopFilterButton, &QPushButton::clicked, this, &UserGUI::handleClearFilter);
    connect(displayFileButton, &QPushButton::clicked, this, &UserGUI::handleDisplayFile);
    connect(playWatchListButton, &QPushButton::clicked, this, &UserGUI::handlePlayWatchlist);
    connect(likeButton, &QPushButton::clicked, this, &UserGUI::handleLike);
    connect(nextButton, &QPushButton::clicked, this, &UserGUI::handleNextTutorial);
}

void UserGUI::handleFilterResult() {
    string presenterFilter = filterPresenterField->text().toStdString();
    filteredTutorials = controller.filterThroughPresenter(presenterFilter);
    position = 0;

    filterPresenterField->clear();
    filterResult->show();
    iterButtonWidget->show();
    addButton->show();
    stopFilterButton->show();

    inputWidget->hide();
    filterButton->hide();

    string intermediate = "1/";
    intermediate.append(std::to_string(filteredTutorials.size()));
    counterLabel->setText(QString::fromStdString(intermediate));

    intermediate = filteredTutorials[0].toString();
    intermediate.pop_back();
    filterResult->setText(QString::fromStdString(intermediate));
}

void UserGUI::handleGoBackwards() {
    position = position == 0 ? this->filteredTutorials.size()-1 : position-1;

    string intermediate;
    intermediate.append(std::to_string(position+1));
    intermediate.append("/");
    intermediate.append(std::to_string(filteredTutorials.size()));
    counterLabel->setText(QString::fromStdString(intermediate));

    intermediate = filteredTutorials[position].toString();
    intermediate.pop_back();
    filterResult->setText(QString::fromStdString(intermediate));

    errorLabel->hide();
}

void UserGUI::handleGoForward() {
    position = position == filteredTutorials.size()-1 ? 0 : position+1;

    string intermediate;
    intermediate.append(std::to_string(position+1));
    intermediate.append("/");
    intermediate.append(std::to_string(filteredTutorials.size()));
    counterLabel->setText(QString::fromStdString(intermediate));

    intermediate = filteredTutorials[position].toString();
    intermediate.pop_back();
    filterResult->setText(QString::fromStdString(intermediate));

    errorLabel->hide();
}

void UserGUI::handleAddTutorialToWatchlist() {
    try {
        controller.addTutorialToWatchList(filteredTutorials[position]);
        errorLabel->hide();

        if (controller.getWatchList().size() == 1)
            playWatchListButton->show();

        vector<Tutorial> emptyVector;
        WatchListModel empty(emptyVector);
        watchListView->setModel(&empty);
        watchListView->setModel(&model);

    } catch (TutorialWithSameLinkException const& excep) {
        errorLabel->show();
    }
}

void UserGUI::handleClearFilter() {
    filterResult->hide();
    errorLabel->hide();
    iterButtonWidget->hide();
    addButton->hide();
    stopFilterButton->hide();
    playWatchListWidget->hide();

    inputWidget->show();
    filterButton->show();

    filteredTutorials.clear();
    position = -1;
}

void UserGUI::handleDisplayFile() {
    controller.saveWatchList();
}

void UserGUI::handlePlayWatchlist() {
    filterButton->hide();
    inputWidget->hide();
    filterResult->hide();
    iterButtonWidget->hide();
    addButton->hide();
    stopFilterButton->hide();
    watchListView->hide();
    displayFileButton->hide();
    playWatchListButton->hide();

    playWatchListWidget->show();
    string currentlyPlaying{"Playing:\n"};
    currentlyPlaying.append(controller.getWatchList()[0].toString());
    QString label = QString::fromStdString(currentlyPlaying);
    playingTutorialLabel->setText(label);

    const Tutorial next_tutorial = controller.getWatchList().front();
    const string command = "firefox " + next_tutorial.getLink();
    system(command.c_str());
}

void UserGUI::handleLike() {
    const string link = controller.getWatchList()[0].getLink();
    controller.incrementTutorialLinkCount(link);
    handleNextTutorial();
}

void UserGUI::handleNextTutorial() {
    model.eraseFirstItem();
    if (controller.getWatchList().size() == 0) {
        playWatchListWidget->hide();

        filterButton->show();
        inputWidget->show();
        watchListView->show();
        displayFileButton->show();

        controller.getWatchList().clear();
        position = -1;
    }
    else {
        string currentlyPlaying{"Playing:\n"};
        currentlyPlaying.append(controller.getWatchList()[0].toString());
        QString label = QString::fromStdString(currentlyPlaying);
        playingTutorialLabel->setText(label);

        const Tutorial next_tutorial = controller.getWatchList().front();
        const string command = "firefox " + next_tutorial.getLink();
        system(command.c_str());
    }
}
