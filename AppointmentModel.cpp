#include "AppointmentModel.h"

#include "TimeUtils.h"
#include "DepartmentService.h"
#include "DutyService.h"
#include "DoctorService.h"

AppointmentModel::AppointmentModel(vector<Appointment> appointments,QObject *parent):
QAbstractTableModel(parent),
appointments(appointments){

}

int AppointmentModel::rowCount(const QModelIndex &parent) const{
    return appointments.size();
}

int AppointmentModel::columnCount(const QModelIndex &parent) const{
    //Id
    //Name
    //Gender
    //Age
    //Tel
    //Time
    //Department
    //Doctor
    return 8;
}

QVariant AppointmentModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if(role!=Qt::DisplayRole)
        return QVariant();

    int row=index.row();
    int column=index.column();

    DutyService dutyService;

    Appointment appointment=appointments.at(row);
    Duty duty=dutyService.getDuty(appointment.getDutyId());
    Doctor doctor=DoctorService().getDoctor(duty.getDoctorId());
    Department department=DepartmentService().getDepartment(doctor.getDepartmentId());
    switch(column){
    case 0:
        return QVariant(appointment.getId());
    case 1:
        return QVariant(appointment.getName().c_str());
    case 2:
        return QVariant(appointment.getGender()==Appointment::GENDER_MALE?"男":"女");
    case 3:
        return QVariant(appointment.getAge());
    case 4:
        return (duty.formatDutyDateAndTimePeriod()+" "+appointment.formatTimePeriod()).c_str();
    case 5:
        return QVariant(appointment.getTelephone().c_str());
    case 6:
        return department.getName().c_str();
    case 7:
        return doctor.getName().c_str();
    }
}

QVariant AppointmentModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch(section){
        case 0:
            return "编号";
        case 1:
            return "姓名";
        case 2:
            return "性别";
        case 3:
            return "年龄";
        case 4:
            return "预约时间";
        case 5:
            return "电话";
        case 6:
            return "门诊部门";
        case 7:
            return "医生";
        }
    }

    return QVariant();
}

void AppointmentModel::addAppointment(const Appointment& appointment){
    beginInsertRows(QModelIndex(),appointments.size(),appointments.size());

    service.addAppointment(appointment);
    appointments.push_back(appointment);

    endInsertRows();
}

void AppointmentModel::deleteAppoinment(int index){
    beginRemoveRows(QModelIndex(),index,index);

    Appointment target=appointments[index];
    service.deleteAppointment(target.getId());

    vector<Appointment> backup=appointments;
    appointments=vector<Appointment>();
    for(int i=0;i<backup.size();i++){
        if(i!=index)
            appointments.push_back(backup[i]);
    }

    endRemoveRows();
}

vector<Appointment> AppointmentModel::getAppointments(){
    return appointments;
}

Appointment AppointmentModel::getAppointmentByIndex(int index){
    return appointments[index];
}
