//
// Created by lkovacs on 5/14/25.
//

#ifndef MAINGUI_H
#define MAINGUI_H

#include <QtWidgets>

#include "operation_stack.h"
#include "../Repository/repository.h"
#include "../watchlistmodel.h"

class MainGUI : public QWidget {
    Q_OBJECT

public:
    explicit MainGUI(QWidget* parent = nullptr);
    ~MainGUI() override;

private:
    QVBoxLayout* layout;
    QPushButton* adminUIButton;
    QPushButton* userUIButton;
    QRadioButton* HTMLChoice;
    QRadioButton* CSVChoice;
    QPushButton* graphUIButton;
    QPushButton* showWatchListButton;

    bool isHTML = true;
    OperationStack* mainOperationStack;
    vector<Tutorial> mainWatchList;
    WatchListModel* watchModel;
    Repository* mainRepo;

    void init();
    void connectSignalsAndSlots();
    void handleHTML();
    void handleCSV();
    void initializeAdminWidget();
    void initializeUserWidget();
    void initializeGraphWidget();
    void initializeWatchListView();
};

#endif //MAINGUI_H
