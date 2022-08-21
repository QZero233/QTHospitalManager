#include "DoctorModel.h"

#include "TimeUtils.h"

#include "DepartmentService.h"

DoctorModel::DoctorModel(vector<Doctor> doctors,QObject *parent):
QAbstractTableModel(parent),
doctors(doctors)
{

}

int DoctorModel::rowCount(const QModelIndex &parent) const{
    return doctors.size();
}

int DoctorModel::columnCount(const QModelIndex &parent) const{
    //Id
    //Name
    //Position
    //Department
    return 4;
}

QVariant DoctorModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();


    //Display role: give rendered data
    //Edit role: give raw data
    if(role!=Qt::DisplayRole && role!=Qt::EditRole)
        return QVariant();

    int row=index.row();
    int column=index.column();

    Doctor doctor=doctors.at(row);

    DoctorService service;

    switch(column){
    case 0:
        return doctor.getId();
    case 1:
        return doctor.getName().c_str();
    case 2:
    {
        if(role==Qt::EditRole){
            return doctor.getPosition();
        }
        string doctorPosition;
        switch(doctor.getPosition()){
        case Doctor::POSITION_PRACTICE:
            doctorPosition="实习医师";
            break;
        case Doctor::POSITION_JUNIOR:
            doctorPosition="高级医师";
            break;
        case Doctor::POSITION_SENIOR:
            doctorPosition="领域专家";
            break;
        }
        return doctorPosition.c_str();
    }
    case 3:
    {
        if(role==Qt::EditRole)
            return doctor.getDepartmentId();
        Department department=DepartmentService().getDepartment(doctor.getDepartmentId());
        return department.getName().c_str();
    }
    default:
        return QVariant();
    }
}

QVariant DoctorModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch(section){
        case 0:
            return "医生编号";
        case 1:
            return "医生姓名";
        case 2:
            return "医生职位";
        case 3:
            return "所属科室";
        }
    }

    return QVariant();
}

Qt::ItemFlags DoctorModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void DoctorModel::addDoctor(const Doctor& doctor){
    beginInsertRows(QModelIndex(),doctors.size(),doctors.size());

    service.addDoctor(doctor);
    doctors.push_back(doctor);

    endInsertRows();
}

void DoctorModel::deleteDoctor(int index){
    beginRemoveRows(QModelIndex(),index,index);

    Doctor target=doctors[index];
    service.deleteDoctor(target.getId());

    vector<Doctor> backup=doctors;
    doctors=vector<Doctor>();
    for(int i=0;i<backup.size();i++){
        if(i!=index)
            doctors.push_back(backup[i]);
    }

    endRemoveRows();
}

vector<Doctor> DoctorModel::getDoctors(){
    return doctors;
}

Doctor DoctorModel::getDoctorByIndex(int index){
    return doctors[index];
}

void DoctorModel::reloadFromDataSource(){
    for(int i=0;i<doctors.size();i++){
        doctors[i]=service.getDoctor(doctors[i].getId());
    }

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(doctors.size() - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

void DoctorModel::setDoctorsAndReload(const vector<Doctor>& doctors){
    this->doctors=doctors;
    reloadFromDataSource();
}

bool DoctorModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid() || role!=Qt::EditRole)
        return false;

    Doctor doctor=doctors[index.row()];
    if(index.column()==1){
       doctor.setName(value.toString().toStdString());
    }else if(index.column()==2){
        doctor.setPosition(value.toInt());
    }else if(index.column()==3){
        doctor.setDepartmentId(value.toInt());
    }
    service.updateDoctor(doctor);
    doctors[index.row()]=doctor;

    return true;
}


