#pragma once

#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include "Department.h"
#include "Doctor.h"
#include "Duty.h"
#include "User.h"
#include <vector>

using namespace std;

class DataSource
{
private:
	vector<Department> departments;
    vector<Appointment> appointments;
    vector<Doctor> doctors;
    vector<Duty> duties;
    vector<User> users;

	string storageFileName;

	static DataSource* instance;

	DataSource(){}
public:
	static DataSource* getInstance();

	void setStorageFilePath(const string& fileName);

	void loadFromFile();
	void saveToFile();

    vector<Department>* getDepartmentsPtr();

    vector<Appointment>* getAppointmentsPtr();

    vector<Doctor>* getDoctorsPtr(){
        return &doctors;
    }

    vector<Duty>* getDutiesPtr(){
        return &duties;
    }

    vector<User>* getUsersPtr(){
        return &users;
    }

};



#endif
