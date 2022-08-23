#ifndef TIMEDUTYMODEL_H
#define TIMEDUTYMODEL_H

#include <QAbstractTableModel>

#include "DutyService.h"

class TimeDutyModel : public QAbstractTableModel
{
public:
    TimeDutyModel(vector<Duty> duties,QDate startDate,int dayCount,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    vector<Duty> getDutiesByIndex(const QModelIndex& index);

    int getTimePeriodByIndex(const QModelIndex& index);

    bool checkIfFull(const QModelIndex& index);
private:
    vector<Duty> duties;
    QDate startDate;
    int dayCount;
};

#endif // TIMEDUTYMODEL_H
