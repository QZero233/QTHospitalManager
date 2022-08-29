#include "TimeDutyModel.h"
#include "AppointmentService.h"

#include "DoctorService.h"

TimeDutyModel::TimeDutyModel(vector<Duty> duties,QDate currentDate,QObject *parent):
QAbstractTableModel(parent),
duties(duties),
currentDate(currentDate)
{
    selectSatisfiedDuties();
}

void TimeDutyModel::selectSatisfiedDuties(){
    satisfied.clear();

    for(Duty duty:duties){
        if(duty.getDutyDate()==currentDate.toJulianDay())
            satisfied.push_back(duty);
    }
}

int TimeDutyModel::columnCount(const QModelIndex &parent) const{
    //Doctor
    //Period
    //Status
    return 3;
}

int TimeDutyModel::rowCount(const QModelIndex &parent) const{
    return satisfied.size();
}

QVariant TimeDutyModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || (role!=Qt::DisplayRole && role!=Qt::EditRole) )
        return QVariant();

    Duty duty=satisfied[index.row()];

    if(index.column()==0){
        //Doctor
        Doctor doctor=DoctorService().getDoctor(duty.getDoctorId());
        return doctor.getName().c_str();
    }else if(index.column()==2){
        //Status
        int dutyCapacity=DutyService().getCapacityById(duty.getId());
        int appointmentCount=AppointmentService().getCountByDutyId(duty.getId());

        bool full=dutyCapacity-appointmentCount<=0;

        if(role==Qt::EditRole)
            return full;
        else
            return full?"已满":"剩余 "+QString::number(dutyCapacity-appointmentCount);
    }else if(index.column()==1){
        return duty.getDutyTimePeriod()==Duty::TIME_PERIOD_AM?"上午":"下午";
    }

}

QVariant TimeDutyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        switch (section) {
        case 0:
            return "医生";
        case 2:
            return "状态";
        case 1:
            return "班次";
        }
    }
    return QVariant();
}

void TimeDutyModel::setCurrentDate(QDate currentDate){
    this->currentDate=currentDate;
    selectSatisfiedDuties();

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

Duty TimeDutyModel::getByIndex(int index){
    return satisfied[index];
}

