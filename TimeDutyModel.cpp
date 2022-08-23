#include "TimeDutyModel.h"
#include "AppointmentService.h"

TimeDutyModel::TimeDutyModel(vector<Duty> duties,QDate startDate,int dayCount,QObject *parent):
QAbstractTableModel(parent),
duties(duties),
startDate(startDate),
dayCount(dayCount){

}

int TimeDutyModel::columnCount(const QModelIndex &parent) const{
    return dayCount;
}

int TimeDutyModel::rowCount(const QModelIndex &parent) const{
    return Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_AM).size()+
            Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_PM).size();
}

QVariant TimeDutyModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || (role!=Qt::DisplayRole && role!=Qt::EditRole) )
        return QVariant();

    long long date=startDate.addDays(index.column()).toJulianDay();

    vector<int> ams=Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_AM);
    vector<int> pms=Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_PM);

    int row=index.row();
    int period;
    int dutyPeriod;
    if(row>=ams.size()){
        dutyPeriod=Duty::TIME_PERIOD_PM;
        period=pms[row-ams.size()];
    }else{
        dutyPeriod=Duty::TIME_PERIOD_AM;
        period=ams[row];
    }

    AppointmentService appointmentService;

    int totalCapacity=0;
    int totalAppointmentCount=0;
    for(Duty duty:duties){
        if(duty.getDutyDate()!=date || duty.getDutyTimePeriod()!=dutyPeriod)
            continue;

        int appointmentCount=appointmentService.getCountByIdAndTimePeriod(duty.getId(),
                                                                          period);
        totalAppointmentCount+=appointmentCount;
        totalCapacity+=duty.getCapacityEachPeriod();
    }

    bool full=totalCapacity-totalAppointmentCount<=0;
    if(role==Qt::EditRole)
        return full;

    return (full?QString("已满"):"空闲") + "(" +QString::number(totalAppointmentCount)+"/"+QString::number(totalCapacity)+")";
}

QVariant TimeDutyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        QDate date=startDate.addDays(section);
        return date.toString("yyyy-MM-dd");
    }else if(orientation==Qt::Vertical && role==Qt::DisplayRole){
        vector<int> ams=Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_AM);
        vector<int> pms=Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_PM);

        int period;
        if(section>=ams.size()){
            period=pms[section-ams.size()];
        }else{
            period=ams[section];
        }

        return Appointment::toStringPeriod(period).c_str();
    }

    return QVariant();
}

vector<Duty> TimeDutyModel::getDutiesByIndex(const QModelIndex& index){
    vector<Duty> result;

    long long date=startDate.addDays(index.column()).toJulianDay();

    vector<int> ams=Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_AM);
    vector<int> pms=Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_PM);

    int row=index.row();
    int period;
    int dutyPeriod;
    if(row>=ams.size()){
        dutyPeriod=Duty::TIME_PERIOD_PM;
        period=pms[row-ams.size()];
    }else{
        dutyPeriod=Duty::TIME_PERIOD_AM;
        period=ams[row];
    }

    for(Duty duty:duties){
        if(duty.getDutyDate()==date && duty.getDutyTimePeriod()==dutyPeriod){
            result.push_back(duty);
        }
    }

    return result;
}

int TimeDutyModel::getTimePeriodByIndex(const QModelIndex& index){
    vector<int> ams=Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_AM);
    vector<int> pms=Appointment::getTimePeriodsByDutyTimePeriod(Duty::TIME_PERIOD_PM);

    int row=index.row();
    int period;
    int dutyPeriod;
    if(row>=ams.size()){
        dutyPeriod=Duty::TIME_PERIOD_PM;
        period=pms[row-ams.size()];
    }else{
        dutyPeriod=Duty::TIME_PERIOD_AM;
        period=ams[row];
    }

    return period;
}

bool TimeDutyModel::checkIfFull(const QModelIndex& index){
    return data(index,Qt::EditRole).toBool();
}
