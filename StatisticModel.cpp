#include "StatisticModel.h"

#include "TimeUtils.h"

StatisticModel::StatisticModel(vector<Department> departments,QObject *parent):
QAbstractTableModel(parent),
departments(departments)
{

}

int StatisticModel::rowCount(const QModelIndex &parent) const{
    return departments.size();
}

int StatisticModel::columnCount(const QModelIndex &parent) const{
    //Name
    //Today status
    //Future status
    //All status
    return 4;
}

QVariant StatisticModel::data(const QModelIndex &index, int role) const{
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

    switch(column){
    case 0:
        return department.getName().c_str();
    case 1:
    {
        int capacity=service.getCapacityByIdAndDate(department.getId(),QDate::currentDate());
        int appointmentCount=service.getAppointmentCountByIdAndDate(department.getId(),
                                                                         QDate::currentDate());

        if(role==Qt::EditRole)
            return capacity==0?0.0:(double)appointmentCount/(double)capacity;

        return QString::number(appointmentCount)+"/"+QString::number(capacity);
    }
    case 2:
    {
        int capacity=service.getCapacityByIdAndDateAfter(department.getId(),QDate::currentDate());
        int appointmentCount=service.getAppointmentCountByIdAndDateAfter(department.getId(),
                                                                         QDate::currentDate());

        if(role==Qt::EditRole)
            return capacity==0?0.0:(double)appointmentCount/(double)capacity;

        return QString::number(appointmentCount)+"/"+QString::number(capacity);
    }
    case 3:
    {
        int capacity=service.getCapacityById(department.getId());
        int appointmentCount=service.getAppointmentCountById(department.getId());

        if(role==Qt::EditRole)
            return capacity==0?0.0:(double)appointmentCount/(double)capacity;

        return QString::number(appointmentCount)+"/"+QString::number(capacity);
    }
    default:
        return QVariant();
    }
}

QVariant StatisticModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch(section){
        case 0:
            return "科室名称";
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


Department StatisticModel::getDepartmentByIndex(int index){
    return departments[index];
}

void StatisticModel::reloadFromDataSource(){
    for(int i=0;i<departments.size();i++){
        departments[i]=service.getDepartment(departments[i].getId());
    }

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

void StatisticModel::setDepartmentsAndReload(const vector<Department>& departments){
    this->departments=departments;
    reloadFromDataSource();
}

