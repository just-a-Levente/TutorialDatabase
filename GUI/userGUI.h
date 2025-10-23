//
// Created by lkovacs on 5/15/25.
//

#ifndef USERGUI_H
#define USERGUI_H

#include <QtWidgets>

#include "../watchlistmodel.h"
#include "../Services/user_service.h"

class UserGUI : public QWidget {
    Q_OBJECT

public:
    UserGUI(UserService& ctrl, WatchListModel& model, QWidget* parent = nullptr);
    ~UserGUI() override;

private:

    // Children of main widget (this)
    QVBoxLayout* mainLayout;
    QPushButton* filterButton;
    QWidget* inputWidget;
    QLabel* filterResult;
    QWidget* iterButtonWidget;
    QLabel* errorLabel;
    QPushButton* addButton;
    QPushButton* stopFilterButton;
    QTableView* watchListView;
    QPushButton* displayFileButton;
    QPushButton* playWatchListButton;
    QWidget* playWatchListWidget;

    // Children of inputWidget
    QFormLayout* inputLayout;
    QLabel* filterPresenterLabel;
    QLineEdit* filterPresenterField;

    // Children of iterButtonWidget
    QHBoxLayout* iterButtonLayout;
    QPushButton* goBackButton;
    QPushButton* goForwardButton;
    QLabel* counterLabel;

    // Children of playWatchListWidget
    QVBoxLayout* playWatchListLayout;
    QLabel* playingTutorialLabel;
    QWidget* playButtonsWidget;
    QHBoxLayout* playButtonsLayout;
    QPushButton* likeButton;
    QPushButton* nextButton;

    UserService& controller;
    WatchListModel& model;

    vector<Tutorial> filteredTutorials;
    int position;

    void init();
    void connectSignalsAndSlots();

    void handleFilterResult();
    void handleGoBackwards();
    void handleGoForward();
    void handleAddTutorialToWatchlist();
    void handleClearFilter();
    void handleDisplayFile();
    void handlePlayWatchlist();
    void handleLike();
    void handleNextTutorial();
};

#endif //USERGUI_H
