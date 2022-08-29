#ifndef DOCTORSTATISTICMODEL_H
#define DOCTORSTATISTICMODEL_H

#include <QAbstractTableModel>

#include "DoctorService.h"

class DoctorStatisticModel : public QAbstractTableModel
{
public:
    DoctorStatisticModel(vector<Doctor> doctors,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    vector<Doctor> doctors;
};

#endif // DOCTORSTATISTICMODEL_H
