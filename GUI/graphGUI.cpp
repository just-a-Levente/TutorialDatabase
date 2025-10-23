//
// Created by lkovacs on 5/22/25.
//

#include "graphGUI.h"

GraphGUI::GraphGUI(Repository& repository, QWidget *parent) : QWidget(parent, Qt::Window), repo(repository) {
    init();
    setAttribute(Qt::WA_DeleteOnClose);
}

GraphGUI::~GraphGUI() {
    parentWidget()->show();
}

void GraphGUI::init() {
    // First we need to extract the data from the repo
    unsigned int maxLikes = -1;
    std::map<std::string, unsigned int> presenterLikeNumbers;
    for (const auto& tutorial : repo.getVector()) {
        const string presenter = tutorial.getPresenter();
        const unsigned int likes = tutorial.getLikes();

        if (!presenterLikeNumbers.contains(presenter))
            presenterLikeNumbers.insert({presenter, likes});
        else
            presenterLikeNumbers[presenter] += likes;
    }

    for (auto presenter : presenterLikeNumbers) {
        if (maxLikes < presenter.second)
            maxLikes = presenter.second;
    }

    // Initializing the bars for each presenter
    int i = 0;
    QBarSet* presenters[presenterLikeNumbers.size()];
    for (const auto& presenter : presenterLikeNumbers) {
        presenters[i] = new QBarSet{QString::fromStdString(presenter.first)};
        *presenters[i] << presenter.second;
        ++i;
    }

    series = new QBarSeries{};
    for (const auto bar : presenters)
        series->append(bar);

    chart = new QChart{};
    chart->addSeries(series);
    chart->setTitle("Number of likes per presenter");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    //QStringList presenterNames{};
    //for (auto presenter : presenterLikeNumbers)
    //    presenterNames.append(QString::fromStdString(presenter.first));
    axisX = new QBarCategoryAxis;
    axisX->append("Likes");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    axisY = new QValueAxis;
    axisY->setRange(0, maxLikes + 1);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    graphView = new QChartView{chart, this};
    graphView->show();

    mainLayout = new QHBoxLayout{this};
    mainLayout->addWidget(graphView);
    setGeometry(0, 0, 800, 550);
}
