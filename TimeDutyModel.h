#ifndef TIMEDUTYMODEL_H
#define TIMEDUTYMODEL_H

#include <QAbstractTableModel>

#include "DutyService.h"

class TimeDutyModel : public QAbstractTableModel
{
public:
    TimeDutyModel(vector<Duty> duties,QDate currentDate,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void selectSatisfiedDuties();
    void setCurrentDate(QDate currentDate);

    Duty getByIndex(int index);
private:
    vector<Duty> duties;
    vector<Duty> satisfied;
    QDate currentDate;
};

#endif // TIMEDUTYMODEL_H
