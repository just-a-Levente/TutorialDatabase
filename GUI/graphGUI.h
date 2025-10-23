//
// Created by lkovacs on 5/22/25.
//

#ifndef GRAPHGUI_H
#define GRAPHGUI_H

#include <QtWidgets>
#include <QtCharts>
#include "../Repository/repository.h"

class GraphGUI : public QWidget {
    Q_OBJECT

public:
    explicit GraphGUI(Repository& repository, QWidget* parent = nullptr);
    ~GraphGUI() override;

private:
    QBarSeries* series;
    QChart* chart;
    QBarCategoryAxis* axisX;
    QValueAxis* axisY;
    QChartView* graphView;
    QHBoxLayout* mainLayout;

    Repository& repo;

    void init();
};

#endif //GRAPHGUI_H
