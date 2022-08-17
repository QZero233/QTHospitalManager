#ifndef DEPARTMENTMODEL_H
#define DEPARTMENTMODEL_H

#include <QAbstractTableModel>

#include "DepartmentService.h"

class DepartmentModel : public QAbstractTableModel
{
public:
    DepartmentModel(vector<Department> departments,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addDepartment(const Department& department);
    void deleteDepartment(int index);

    vector<Department> getDepartments();
    Department getDepartmentByIndex(int index);

    void reloadFromDataSource();
private:
    vector<Department> departments;

    DepartmentService service;
};

#endif // DEPARTMENTMODEL_H
