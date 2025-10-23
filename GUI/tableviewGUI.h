//
// Created by lkovacs on 5/31/25.
//

#ifndef TABLEVIEWGUI_H
#define TABLEVIEWGUI_H

#include <QtWidgets>

#include "../watchlistmodel.h"

class ViewGUI : public QWidget {
    Q_OBJECT

public:
    ViewGUI(WatchListModel& model, QWidget* parent = nullptr);
    ~ViewGUI() override;

private:
    QVBoxLayout* mainLayout;
    QTableView* watchListView;
    WatchListModel& model;

    void init();
};

#endif //TABLEVIEWGUI_H
