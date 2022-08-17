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

public:
	static const int GENDER_FEMALE = 0;
	static const int GENDER_MALE = 1;

    //TODO put argyments check into service
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
		if (gender != 0 && gender != 1) {
			throw invalid_argument("Gender must be 0 or 1");
		}

		this->gender = gender;
	}

	int getGender() const {
		return gender;
	}

	void setAge(int age) {
		if (age <= 0) {
			throw invalid_argument("Age must be greater than 0");
		}

		this->age = age;
	}

	int getAge() const {
		return age;
	}

	void setAppointmentTime(long time) {
		if (time <= 0) {
			throw invalid_argument("Time must be greater than 0");
		}

		appointmentTime = time;
	}

	long getAppointmentTime() const {
		return appointmentTime;
	}
	
};
#endif

