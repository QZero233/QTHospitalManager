#ifndef DUTY_H
#define DUTY_H

#include <string>
#include <QDate>

#include <vector>

using namespace std;

class Duty
{
public:
    static const int TIME_PERIOD_AM=1;
    static const int TIME_PERIOD_PM=2;

    Duty():
        id(-1),
        doctorId(-1),
        dutyTimePeriod(-1),
        dutyDate(-1),
        capacityEachPeriod(-1){}

    Duty(int id,int doctorId,int dutyTimePeriod,long long dutyDate,int capacityEachPeriod):
        id(id),
        doctorId(doctorId),
        dutyTimePeriod(dutyTimePeriod),
        dutyDate(dutyDate),
        capacityEachPeriod(capacityEachPeriod){}

    void setId(int id){
        this->id=id;
    }

    int getId() const{
        return id;
    }

    void setDoctorId(int doctorId){
        this->doctorId=doctorId;
    }

    int getDoctorId() const{
        return doctorId;
    }

    void setDutyTimePeriod(int dutyTimePeriod){
        this->dutyTimePeriod=dutyTimePeriod;
    }

    int getDutyTimePeriod() const{
        return dutyTimePeriod;
    }

    void setDutyDate(long long dutyDate){
        this->dutyDate=dutyDate;
    }

    long long getDutyDate() const{
        return dutyDate;
    }

    void setCapacityEachPeriod(int capacity){
        capacityEachPeriod=capacity;
    }

    int getCapacityEachPeriod() const{
        return capacityEachPeriod;
    }

    string formatDutyTimePeriod(){
        switch(dutyTimePeriod){
        case TIME_PERIOD_AM:
            return "上午";
        case TIME_PERIOD_PM:
            return "下午";
        default:
            return "";
        }
    }

    string formatDutyDateAndTimePeriod(){
        QDate date=QDate::fromJulianDay(dutyDate);
        QString formattedDate=date.toString("yyyy-MM-dd ");
        return formattedDate.toStdString()+formatDutyTimePeriod();
    }

private:
    int id;
    int doctorId;
    int dutyTimePeriod;
    long long dutyDate;
    int capacityEachPeriod;
};

#endif // DUTY_H
