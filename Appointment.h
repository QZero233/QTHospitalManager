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
	long appointmentTime;
    int departmentId;

public:
	static const int GENDER_FEMALE = 0;
	static const int GENDER_MALE = 1;

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

	void setAppointmentTime(long time) {
		appointmentTime = time;
	}

	long getAppointmentTime() const {
		return appointmentTime;
	}

    void setDepartmentId(int id){
        this->departmentId=id;
    }

    int getDepartmentId() const{
        return departmentId;
    }
	
};
#endif

