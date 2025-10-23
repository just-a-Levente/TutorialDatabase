//
// Created by lkovacs on 5/31/25.
//

#ifndef WATCHLISTMODEL_H
#define WATCHLISTMODEL_H

#include "Domain/tutorial.h"
#include <QtWidgets>
#include <vector>
using std::vector;

class WatchListModel : public QAbstractTableModel {
    Q_OBJECT

    vector<Tutorial>& tutorials;

public:
    explicit WatchListModel(vector<Tutorial>& tutorials, QObject* parent = nullptr);
    WatchListModel(const WatchListModel& otherModel);
    vector<Tutorial>& getWatchList() const;
    void addNewItem(Tutorial newTutorial);
    void eraseFirstItem();

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif //WATCHLISTMODEL_H
