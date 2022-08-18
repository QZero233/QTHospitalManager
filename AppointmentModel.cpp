#include "AppointmentModel.h"

#include "TimeUtils.h"
#include "DepartmentService.h"

AppointmentModel::AppointmentModel(vector<Appointment> appointments,QObject *parent):
QAbstractTableModel(parent),
appointments(appointments),
departmentId(-1),
singleDepartmentMode(false){

}

AppointmentModel::AppointmentModel(int departmentId,QObject *parent):
QAbstractTableModel(parent),
departmentId(departmentId),
singleDepartmentMode(true){
    appointments=service.getAllAppointmentsByDepartmentId(departmentId);
}

int AppointmentModel::rowCount(const QModelIndex &parent) const{
    return appointments.size();
}

int AppointmentModel::columnCount(const QModelIndex &parent) const{
    if(singleDepartmentMode)
        return 6;
    else
        return 7;
}

QVariant AppointmentModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();


    //Display role: give rendered data
    //Edit role: give raw data
    if(role!=Qt::DisplayRole && role!=Qt::EditRole)
        return QVariant();

    int row=index.row();
    int column=index.column();

    Appointment appointment=appointments.at(row);
    switch(column){
    case 0:
        return QVariant(appointment.getId());
    case 1:
        return QVariant(appointment.getName().c_str());
    case 2:
        if(role==Qt::DisplayRole)
            return QVariant(appointment.getGender()==Appointment::GENDER_MALE?"男":"女");
        else if(role==Qt::EditRole)
            return QVariant(appointment.getGender());
    case 3:
        return QVariant(appointment.getAge());
    case 4:
        if(role==Qt::DisplayRole)
            return QVariant(TimeUtils::formatTimeStamp(appointment.getAppointmentTime()));
        else if(role==Qt::EditRole)
            return QVariant((long long)appointment.getAppointmentTime());
    case 5:
        return QVariant(appointment.getTelephone().c_str());
    case 6:
        DepartmentService departmentService;
        Department department=departmentService.getDepartment(appointment.getDepartmentId());
        return QVariant(department.getName().c_str());
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
        }
    }

    return QVariant();
}

bool AppointmentModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid() || role!=Qt::EditRole)
        return false;

    int row=index.row();
    int column=index.column();

    Appointment appointment=appointments[row];
    switch(column){
    case 1:
        appointment.setName(value.toString().toStdString());
        break;
    case 2:
        appointment.setGender(value.toInt());
        break;
    case 3:
        appointment.setAge(value.toInt());
        break;
    case 4:
        appointment.setAppointmentTime(value.toLongLong());
        break;
    case 5:
        appointment.setTelephone(value.toString().toStdString());
    }

    service.updateAppointment(appointment);
    appointments[row]=appointment;

    emit dataChanged(index, index, {role});
    return true;
}

Qt::ItemFlags AppointmentModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
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
