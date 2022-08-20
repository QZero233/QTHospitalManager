#pragma once
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <stdexcept>

using namespace std;

class Appointment{
private:
	int id;
	string name;
	string telephone;
	int gender;
	int age;
    int dutyId;

public:
	static const int GENDER_FEMALE = 0;
	static const int GENDER_MALE = 1;

    Appointment():
        id(-1),
        name(""),
        telephone(""),
        gender(-1),
        age(-1),
        dutyId(-1){}

    Appointment(int id,string name,string telephone,int gender,int age,int dutyId):
        id(id),
        name(name),
        telephone(telephone),
        gender(gender),
        age(age),
        dutyId(dutyId){}

	void setId(int id) {
		this->id = id;
	}

	int getId() const{
		return id;
	}

	void setName(const string& name) {
		this->name = name;
	}

	string getName() const {
		return name;
	}

	void setTelephone(const string& telephone) {
		this->telephone = telephone;
	}

	string getTelephone() const {
		return telephone;
	}

	void setGender(int gender) {
		this->gender = gender;
	}

	int getGender() const {
		return gender;
	}

	void setAge(int age) {
		this->age = age;
	}

	int getAge() const {
		return age;
	}

    void setDutyId(int dutyId){
        this->dutyId=dutyId;
    }

    int getDutyId() const{
        return dutyId;
    }
	
};
#endif

