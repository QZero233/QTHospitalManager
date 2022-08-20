#ifndef DOCTORMODEL_H
#define DOCTORMODEL_H

#include <QAbstractTableModel>

#include "DoctorService.h"

class DoctorModel : public QAbstractTableModel
{
public:
    DoctorModel(vector<Doctor> doctors,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void addDoctor(const Doctor& doctor);
    void deleteDoctor(int index);

    vector<Doctor> getDoctors();
    Doctor getDoctorByIndex(int index);

    void reloadFromDataSource();

    void setDoctorsAndReload(const vector<Doctor>& doctors);
private:
    vector<Doctor> doctors;

    DoctorService service;
};

#endif // DOCTORMODEL_H
