#ifndef DUTY_H
#define DUTY_H

#include <string>
#include <QDate>

using namespace std;

class Duty
{
public:
    static const int TIME_AM=1;
    static const int TIME_PM=2;

    Duty():
        id(-1),
        doctorId(-1),
        departmentId(-1),
        dutyTime(-1),
        dutyDate(-1){}

    Duty(int id,int doctorId,int departmentId,int dutyTime,long long dutyDate):
        id(id),
        doctorId(doctorId),
        departmentId(departmentId),
        dutyTime(dutyTime),
        dutyDate(dutyDate){}

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

    void setDepartmentId(int departmentId){
        this->departmentId=departmentId;
    }

    int getDepartmentId() const{
        return departmentId;
    }

    void setDutyTime(int dutyTime){
        this->dutyTime=dutyTime;
    }

    int getDutyTime() const{
        return dutyTime;
    }

    void setDutyDate(long long dutyDate){
        this->dutyDate=dutyDate;
    }

    long long getDutyDate() const{
        return dutyDate;
    }

    string formatDutyTime(){
        switch(dutyTime){
        case TIME_AM:
            return "上午";
        case TIME_PM:
            return "下午";
        default:
            return "";
        }
    }

    string formatDutyDateTime(){
        QDate date=QDate::fromJulianDay(dutyDate);
        QString formattedDate=date.toString("yyyy-MM-dd ");
        return formattedDate.toStdString()+formatDutyTime();
    }
private:
    int id;
    int doctorId;
    int departmentId;
    int dutyTime;
    long long dutyDate;
};

#endif // DUTY_H
