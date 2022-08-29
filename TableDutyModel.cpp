#include "TableDutyModel.h"

#include "DoctorService.h"
#include "DepartmentService.h"
#include "AppointmentService.h"

TableDutyModel::TableDutyModel(vector<Duty> duties,QDate startDate,int dayCount,QObject *parent):
DutyModel(vector<Duty>(),parent),
startDate(startDate),
dayCount(dayCount)
{
    this->duties=duties;
    loadAMandPM();
}

void TableDutyModel::setDateAndCount(QDate date,int count){
    startDate=date;
    dayCount=count;

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

int TableDutyModel::rowCount(const QModelIndex &parent) const{
    return rows;
}

int TableDutyModel::columnCount(const QModelIndex &parent) const{
    return dayCount;
}

QVariant TableDutyModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if(role!=Qt::DisplayRole && role!=Qt::EditRole)
        return QVariant();

    if(index.row()==3 && index.column()==1){
        int i=0;
        i++;
    }

    Duty duty;
    if(index.row()>=biggestAM){
        //PM
        QList<Duty> amList=am.value(startDate.addDays(index.column()).toJulianDay());
        QList<Duty> pmList=pm.value(startDate.addDays(index.column()).toJulianDay());
        int i=index.row()-biggestAM;

        if(i>=pmList.size())
            return QVariant();
        duty=pmList[i];
    }else{
        //AM
        QList<Duty> amList=am.value(startDate.addDays(index.column()).toJulianDay());
        if(index.row()>=amList.size())
            return QVariant();
        duty=amList[index.row()];
    }


    Doctor doctor=DoctorService().getDoctor(duty.getDoctorId());
    Department department=DepartmentService().getDepartment(doctor.getDepartmentId());

    DutyService service;
    AppointmentService appointmentService;
    int capacity=service.getCapacityById(duty.getId());
    int current=appointmentService.getCountByDutyId(duty.getId());
    bool occupied=capacity-current<=0;

    QString departmentName=department.getName().c_str();
    QString doctorName=doctor.getName().c_str();
    QString dutyDate=duty.formatDutyDateAndTimePeriod().c_str();
    QString status=occupied?"已满":"剩余 "+QString::number(capacity-current);

    return departmentName+" "+doctorName+" "+dutyDate;

}

QVariant TableDutyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation==Qt::Horizontal && role==Qt::DisplayRole){
        QDate date=startDate.addDays(section);
        return date.toString("yyyy-MM-dd");
    }else if(orientation==Qt::Vertical && role==Qt::DisplayRole){
        if(section>=biggestAM)
            return "下午";
        else
            return "上午";
    }

    return QVariant();
}

void TableDutyModel::loadAMandPM(){
    am.clear();
    pm.clear();
    biggestAM=0;
    biggestPM=0;
    for(Duty duty:duties){
        if(duty.getDutyTimePeriod()==Duty::TIME_PERIOD_AM){
            QList<Duty> list=am.value(duty.getDutyDate());
            list.append(duty);
            am.insert(duty.getDutyDate(),list);
        }else{
            QList<Duty> list=pm.value(duty.getDutyDate());
            list.append(duty);
            pm.insert(duty.getDutyDate(),list);
        }
    }

    QList<QList<Duty>> amList=am.values();
    for(QList<Duty> list:amList){
        if(list.size()>biggestAM)
            biggestAM=list.size();
    }

    QList<QList<Duty>> pmList=pm.values();
    for(QList<Duty> list:pmList){
        if(list.size()>biggestPM)
            biggestPM=list.size();
    }

    rows=biggestAM+biggestPM;
}

void TableDutyModel::addDuty(const Duty& duty){
    service.addDuty(duty);
    duties.push_back(duty);
    loadAMandPM();

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}

void TableDutyModel::deleteDuty(int row,int column){
    Duty target;
    if(row>=biggestAM){
        //PM
        QList<Duty> amList=am.value(startDate.addDays(column).toJulianDay());
        QList<Duty> pmList=pm.value(startDate.addDays(column).toJulianDay());
        int i=row-biggestAM;

        if(i>=pmList.size())
            return;
        target=pmList[i];
    }else{
        //AM
        QList<Duty> amList=am.value(startDate.addDays(column).toJulianDay());
        if(row>=amList.size())
            return;
        target=amList[row];
    }

    service.deleteDuty(target.getId());

    vector<Duty> backup=duties;
    duties=vector<Duty>();
    for(int i=0;i<backup.size();i++){
        if(backup[i].getId()!=target.getId())
            duties.push_back(backup[i]);
    }

    loadAMandPM();

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);
    emit layoutChanged();
}
