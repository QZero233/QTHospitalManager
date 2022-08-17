#pragma once
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <stdexcept>
#include <vector>

#include "Appointment.h"

using namespace std;

class Department{
private:
	int id;
	string name;
	int idOfDutyDoctor;
    long appointmentStartTime=-1;
    long appointmentEndTime=-1;
	int capacity;
	string address;
	string telephone;

	vector<Appointment> appointments;

public:
	Department() :
	id(-1),name("empty"),idOfDutyDoctor(-1),appointmentStartTime(-1),appointmentEndTime(-1),
	capacity(-1),address("empty"),telephone("empty") {

	}

	Department(int id,const string& name,int idOfDutyDoctor,long appointmentStartTime,
		long appointmentEndTime, int capacity, string address, string telephone) {
		setId(id);
		setName(name);
		setIdOfDutyDoctor(idOfDutyDoctor);
		setAppointmentStartTime(appointmentStartTime);
		setAppointmentEndTime(appointmentEndTime);
		setCapacity(capacity);
		setAddress(address);
		setTelephone(telephone);
	}

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

	void setIdOfDutyDoctor(int id) {
		idOfDutyDoctor = id;
	}

	int getIdOfDutyDoctor() const {
		return idOfDutyDoctor;
	}

    void setAppointmentStartTime(long time) {
		appointmentStartTime = time;
	}

	long getAppointmentStartTime() const {
		return appointmentStartTime;
	}
	
	void setAppointmentEndTime(long time) {
		appointmentEndTime = time;
	}

	long getAppointmentEndTime() const {
		return appointmentEndTime;
	}

	void setCapacity(int capacity) {
		this->capacity = capacity;
	}

	int getCapacity() const {
		return capacity;
	}

	void setAddress(const string& address) {
		this->address = address;
	}

	string getAddress() const {
		return address;
	}

	void setTelephone(const string& tel) {
		telephone = tel;
	}

	string getTelephone() const {
		return telephone;
	}

	vector<Appointment> getAppointments() const {
		return appointments;
	}

	vector<Appointment>* getAppointmentsPtr() {
		return &appointments;
	}

	void setAppointments(const vector<Appointment>& appointments) {
		this->appointments = appointments;
	}
};

#endif

