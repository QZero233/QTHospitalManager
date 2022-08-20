#include "DepartmentModel.h"

#include "TimeUtils.h"

DepartmentModel::DepartmentModel(vector<Department> departments,QObject *parent):
QAbstractTableModel(parent),
departments(departments)
{

}

int DepartmentModel::rowCount(const QModelIndex &parent) const{
    return departments.size();
}

int DepartmentModel::columnCount(const QModelIndex &parent) const{
    //Id
    //Name
    //Address
    //Tel
    //Capacity
    //Status
    return 6;
}

QVariant DepartmentModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();


    //Display role: give rendered data
    //Edit role: give raw data
    if(role!=Qt::DisplayRole && role!=Qt::EditRole)
        return QVariant();

    int row=index.row();
    int column=index.column();

    Department department=departments.at(row);

    DepartmentService service;
    int capacity=service.getCapacityById(department.getId());
    int appointmentCount=service.getAppointmentCountById(department.getId());

    switch(column){
    case 0:
        return department.getId();
    case 1:
        return department.getName().c_str();
    case 2:
        return department.getAddress().c_str();
    case 3:
        return department.getTelephone().c_str();
    case 4:
    {
        return (to_string(appointmentCount)+"/"+to_string(capacity)).c_str();
    }
    case 5:
    {
        bool full=(capacity-appointmentCount<=0);
        if(role==Qt::DisplayRole){
            if(full)
                return "已满";
            else
                return ("剩余 "+to_string(capacity-appointmentCount)+" 个名额").c_str();
        }else{
            return full;
        }
    }
    default:
        return QVariant();
    }
}

QVariant DepartmentModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch(section){
        case 0:
            return "门诊编号";
        case 1:
            return "门诊名称";
        case 2:
            return "门诊地址";
        case 3:
            return "联系电话";
        case 4:
            return "当前预约数/总容量";
        case 5:
            return "状态";
        }
    }

    return QVariant();
}

Qt::ItemFlags DepartmentModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void DepartmentModel::addDepartment(const Department& department){
    beginInsertRows(QModelIndex(),departments.size(),departments.size());

    service.addDepartment(department);
    departments.push_back(department);

    endInsertRows();
}

void DepartmentModel::deleteDepartment(int index){
    beginRemoveRows(QModelIndex(),index,index);

    Department target=departments[index];
    service.deleteDepartment(target.getId());

    vector<Department> backup=departments;
    departments=vector<Department>();
    for(int i=0;i<backup.size();i++){
        if(i!=index)
            departments.push_back(backup[i]);
    }

    endRemoveRows();
}

vector<Department> DepartmentModel::getDepartments(){
    return departments;
}

Department DepartmentModel::getDepartmentByIndex(int index){
    return departments[index];
}

void DepartmentModel::reloadFromDataSource(){
    for(int i=0;i<departments.size();i++){
        departments[i]=service.getDepartment(departments[i].getId());
    }

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(departments.size() - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

void DepartmentModel::setDepartmentsAndReload(const vector<Department>& departments){
    this->departments=departments;
    reloadFromDataSource();
}

