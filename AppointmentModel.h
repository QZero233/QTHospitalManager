#ifndef APPOINTMENTMODEL_H
#define APPOINTMENTMODEL_H

#include <QAbstractTableModel>

#include "AppointmentService.h"

class AppointmentModel : public QAbstractTableModel
{
public:
    AppointmentModel(vector<Appointment> appointments,QObject *parent=nullptr);
    AppointmentModel(int departmentId,QObject *parent=nullptr);

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addAppointment(const Appointment& appointment);
    void deleteAppoinment(int index);

    vector<Appointment> getAppointments();
    Appointment getAppointmentByIndex(int index);
private:
    vector<Appointment> appointments;
    int departmentId;
    bool singleDepartmentMode;

    AppointmentService service;
};

#endif // APPOINTMENTMODEL_H
