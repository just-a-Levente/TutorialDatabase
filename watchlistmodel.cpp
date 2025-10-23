//
// Created by lkovacs on 5/31/25.
//

#include "watchlistmodel.h"

WatchListModel::WatchListModel(vector<Tutorial>& tutorials, QObject *parent) : QAbstractTableModel(parent), tutorials(tutorials) {
}

WatchListModel::WatchListModel(const WatchListModel &otherModel): tutorials(otherModel.getWatchList()) {
}

vector<Tutorial> & WatchListModel::getWatchList() const {
    return tutorials;
}

void WatchListModel::addNewItem(Tutorial newTutorial) {
    tutorials.push_back(newTutorial);
    const int row = rowCount(QModelIndex()) - 1;

    setData(index(row, 0), QVariant(QString::fromStdString(newTutorial.getLink())));
    setData(index(row, 1), QVariant(QString::fromStdString(newTutorial.getTitle())));
    setData(index(row, 2), QVariant(QString::fromStdString(newTutorial.getPresenter())));
    t_duration time = newTutorial.getDuration();
    QString duration = QString::number(time.first);
    duration += ":";
    duration += QString::number(time.second);
    setData(index(row, 3), QVariant(duration));
    setData(index(row, 4), QVariant(newTutorial.getLikes()));
}

void WatchListModel::eraseFirstItem() {
    tutorials.erase(tutorials.begin());
    removeRow(0, QModelIndex());
}

int WatchListModel::rowCount(const QModelIndex &parent) const {
    return tutorials.size();
}

int WatchListModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant WatchListModel::data(const QModelIndex &index, int role) const {
    if (role == Qt::DisplayRole) {
        switch (index.column()) {
            case 0:{
                string link = tutorials[index.row()].getLink();
                return QString::fromStdString(link);
            }
            case 1: {
                string title = tutorials[index.row()].getTitle();
                return QString::fromStdString(title);
            }
            case 2: {
                string presenter = tutorials[index.row()].getPresenter();
                return QString::fromStdString(presenter);
            }
            case 3: {
                t_duration time = tutorials[index.row()].getDuration();
                QString duration = QString::number(time.first);
                duration += ":";
                duration += QString::number(time.second);
                return duration;
            }
            case 4: {
                return QString::number(tutorials[index.row()].getLikes());
            }
        }
    }

    return QVariant();
}

bool WatchListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;

        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant WatchListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return QString("Link");
            case 1:
                return QString("Title");
            case 2:
                return QString("Presenter");
            case 3:
                return QString("Duration");
            case 4:
                return QString("Likes");
        }
    }
    return QVariant();
}
