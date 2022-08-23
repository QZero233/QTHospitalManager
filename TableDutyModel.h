#ifndef TABLEDUTYMODEL_H
#define TABLEDUTYMODEL_H

#include "DutyModel.h"

#include <QMap>

class TableDutyModel : public DutyModel
{
public:
    TableDutyModel(vector<Duty> duties,QDate startDate,int dayCount,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual void addDuty(const Duty& duty) override;
    void deleteDuty(int row,int column);
private:
    vector<Duty> duties;

    DutyService service;

    QDate startDate;
    int dayCount;

    QMap<long long,QList<Duty>> am;
    QMap<long long,QList<Duty>> pm;

    int rows;
    int biggestAM=0;
    int biggestPM=0;

    void loadAMandPM();
};

#endif // TABLEDUTYMODEL_H
