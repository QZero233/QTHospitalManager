#ifndef DUTYMODEL_H
#define DUTYMODEL_H

#include <QAbstractTableModel>

#include "DutyService.h"

class DutyModel : public QAbstractTableModel
{
public:
    DutyModel(vector<Duty> duties,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual void addDuty(const Duty& duty);
    virtual void deleteDuty(int index);

    vector<Duty> getDuties();
    Duty getDutyByIndex(int index);

    void reloadFromDataSource();

    void setDutiesAndReload(const vector<Duty>& duties);

    void sortByStatus();

    void setTimeFixed(int timePeriod);
protected:
    vector<Duty> duties;

    DutyService service;

    bool timeFixed=false;
    int timePeriod=-1;
};
#endif // DUTYMODEL_H
