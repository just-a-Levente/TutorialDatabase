//
// Created by lkovacs on 5/31/25.
//

#include "tableviewGUI.h"

ViewGUI::ViewGUI(WatchListModel &model, QWidget *parent) : QWidget(parent, Qt::Window), model(model){
    init();
    setAttribute(Qt::WA_DeleteOnClose);
}

ViewGUI::~ViewGUI() {
    parentWidget()->show();
}

void ViewGUI::init() {
    setGeometry(100, 100, 800, 400);
    mainLayout = new QVBoxLayout{this};
    watchListView = new QTableView{};
    mainLayout->addWidget(watchListView);
    watchListView->setModel(&model);
}
