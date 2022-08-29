#ifndef STATISTICMODEL_H
#define STATISTICMODEL_H

#include <QAbstractTableModel>

#include "DepartmentService.h"

class StatisticModel : public QAbstractTableModel
{
public:
    StatisticModel(vector<Department> departments,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Department getDepartmentByIndex(int index);

    void reloadFromDataSource();

    void setDepartmentsAndReload(const vector<Department>& departments);
private:
    vector<Department> departments;

    DepartmentService service;
};


#endif // STATISTICMODEL_H
