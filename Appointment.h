#pragma once
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <stdexcept>

#include <vector>

#define TIME_PERIOD_AM_1 1 //8:00-10:00
#define TIME_PERIOD_AM_2 2 //10:00-12:00
#define TIME_PERIOD_PM_1 3 //13:00-15:00
#define TIME_PERIOD_PM_2 4 //15:00-17:00

#include "Duty.h"

using namespace std;

class Appointment{
private:
	int id;
    string username;
    int dutyId;
    int timePeriod;

public:

    Appointment():
        id(-1),
        username(""),
        dutyId(-1),
        timePeriod(-1){}

    Appointment(int id,string username,int dutyId,int timePeriod):
        id(id),
        username(username),
        dutyId(dutyId),
        timePeriod(timePeriod){}

	void setId(int id) {
		this->id = id;
	}

	int getId() const{
		return id;
	}

    void setUsername(string username){
        this->username=username;
    }

    string getUsername() const{
        return username;
    }

    void setDutyId(int dutyId){
        this->dutyId=dutyId;
    }

    int getDutyId() const{
        return dutyId;
    }

    void setTimePeriod(int t){
        timePeriod=t;
    }

    int getTimePeriod() const{
        return timePeriod;
    }

    static vector<int> getTimePeriodsByDutyTimePeriod(int timePeriod){
        vector<int> result;

        if(timePeriod==Duty::TIME_PERIOD_AM){
            result.push_back(TIME_PERIOD_AM_1);
            result.push_back(TIME_PERIOD_AM_2);
        }else{
            result.push_back(TIME_PERIOD_PM_1);
            result.push_back(TIME_PERIOD_PM_2);
        }

        return result;
    }

    string formatTimePeriod(){
        return toStringPeriod(timePeriod);
    }

    static string toStringPeriod(int period){
        switch(period){
        case TIME_PERIOD_AM_1:
            return "8:00-10:00";
        case TIME_PERIOD_AM_2:
            return "10:00-12:00";
        case TIME_PERIOD_PM_1:
            return "13:00-15:00";
        case TIME_PERIOD_PM_2:
            return "15:00-17:00";
        default:
            return "";
        }
    }
	
};
#endif

