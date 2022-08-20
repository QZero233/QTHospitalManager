#include "DutyModel.h"

#include "TimeUtils.h"

#include "DoctorService.h"
#include "DepartmentService.h"
#include "AppointmentService.h"

DutyModel::DutyModel(vector<Duty> duties,QObject *parent):
QAbstractTableModel(parent)
{

    //Sort duties by status
    vector<Duty> vacant,occupied;
    AppointmentService appointmentService;
    for(Duty duty:duties){
        if(appointmentService.existByDutyId(duty.getId()))
            occupied.push_back(duty);
        else
            vacant.push_back(duty);
    }

    this->duties=vacant;
    for(Duty duty:occupied){
        this->duties.push_back(duty);
    }
}

int DutyModel::rowCount(const QModelIndex &parent) const{
    return duties.size();
}

int DutyModel::columnCount(const QModelIndex &parent) const{
    //Id
    //Doctor name
    //Time
    //Department name
    //Status
    return 5;
}

QVariant DutyModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if(role!=Qt::DisplayRole && role!=Qt::EditRole)
        return QVariant();

    int row=index.row();
    int column=index.column();

    Duty duty=duties.at(row);
    Doctor doctor=DoctorService().getDoctor(duty.getDoctorId());
    Department department=DepartmentService().getDepartment(duty.getDepartmentId());
    bool occupied=AppointmentService().existByDutyId(duty.getId());
    switch(column){
    case 0:
        return duty.getId();
    case 1:
        return doctor.getName().c_str();
    case 2:
        return duty.formatDutyDateTime().c_str();
    case 3:
        return department.getName().c_str();
    case 4:
        if(role==Qt::DisplayRole)
            return occupied?"已被预约":"空闲";
        else
            return occupied;
    default:
        return QVariant();
    }
}

QVariant DutyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch(section){
        case 0:
            return "编号";
        case 1:
            return "医生姓名";
        case 2:
            return "时间";
        case 3:
            return "科室名称";
        case 4:
            return "状态";
        }
    }

    return QVariant();
}

void DutyModel::addDuty(const Duty& duty){
    beginInsertRows(QModelIndex(),duties.size(),duties.size());

    service.addDuty(duty);
    duties.push_back(duty);

    endInsertRows();
}

void DutyModel::deleteDuty(int index){
    beginRemoveRows(QModelIndex(),index,index);

    Duty target=duties[index];
    service.deleteDuty(target.getId());

    vector<Duty> backup=duties;
    duties=vector<Duty>();
    for(int i=0;i<backup.size();i++){
        if(i!=index)
            duties.push_back(backup[i]);
    }

    endRemoveRows();
}

vector<Duty> DutyModel::getDuties(){
    return duties;
}

Duty DutyModel::getDutyByIndex(int index){
    return duties[index];
}

void DutyModel::reloadFromDataSource(){
    for(int i=0;i<duties.size();i++){
        duties[i]=service.getDuty(duties[i].getId());
    }

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(duties.size() - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

void DutyModel::setDutiesAndReload(const vector<Duty>& duties){
    //Sort duties by status
    vector<Duty> vacant,occupied;
    AppointmentService appointmentService;
    for(Duty duty:duties){
        if(appointmentService.existByDutyId(duty.getId()))
            occupied.push_back(duty);
        else
            vacant.push_back(duty);
    }

    this->duties=vacant;
    for(Duty duty:occupied){
        this->duties.push_back(duty);
    }
    reloadFromDataSource();
}


