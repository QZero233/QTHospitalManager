#include "DoctorStatisticModel.h"

#include "TimeUtils.h"

DoctorStatisticModel::DoctorStatisticModel(vector<Doctor> doctors,QObject *parent):
QAbstractTableModel(parent),
doctors(doctors)
{

}

int DoctorStatisticModel::rowCount(const QModelIndex &parent) const{
    return doctors.size();
}

int DoctorStatisticModel::columnCount(const QModelIndex &parent) const{
    //Name
    //Today status
    //Future status
    //All status
    return 4;
}

QVariant DoctorStatisticModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();


    //Display role: give rendered data
    //Edit role: give raw data
    if(role!=Qt::DisplayRole && role!=Qt::EditRole)
        return QVariant();

    int row=index.row();
    int column=index.column();

    Doctor doctor=doctors[row];
    DoctorService service;


    switch(column){
    case 0:
        return doctor.getName().c_str();
    case 1:
    {
        int capacity=service.getCapacityByDoctorIdAndDate(doctor.getId(),QDate::currentDate());
        int appointmentCount=service.getAppointmentCountByDoctorIdAndDate(doctor.getId(),
                                                                         QDate::currentDate());

        if(role==Qt::EditRole)
            return capacity==0?0.0:(double)appointmentCount/(double)capacity;

        return QString::number(appointmentCount)+"/"+QString::number(capacity);
    }
    case 2:
    {
        int capacity=service.getCapacityByDoctorIdAndDateAfter(doctor.getId(),QDate::currentDate());
        int appointmentCount=service.getAppointmentCountByDoctorIdAndDateAfter(doctor.getId(),
                                                                         QDate::currentDate());

        if(role==Qt::EditRole)
            return capacity==0?0.0:(double)appointmentCount/(double)capacity;

        return QString::number(appointmentCount)+"/"+QString::number(capacity);
    }
    case 3:
    {
        int capacity=service.getCapacityByDoctorId(doctor.getId());
        int appointmentCount=service.getAppointmentCountByDoctorId(doctor.getId());

        if(role==Qt::EditRole)
            return capacity==0?0.0:(double)appointmentCount/(double)capacity;

        return QString::number(appointmentCount)+"/"+QString::number(capacity);
    }
    default:
        return QVariant();
    }
}

QVariant DoctorStatisticModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch(section){
        case 0:
            return "医生姓名";
        case 1:
            return "当日预约/当日容量";
        case 2:
            return "未来预约/未来容量";
        case 3:
            return "所有预约/所有容量";
        }
    }

    return QVariant();
}

/*
 *
    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
    */


