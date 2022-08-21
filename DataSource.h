#pragma once

#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include "Department.h"
#include "Doctor.h"
#include "Duty.h"
#include <vector>

using namespace std;

class DataSource
{
private:
	vector<Department> departments;
    vector<Appointment> appointments;
    vector<Doctor> doctors;
    vector<Duty> duties;

    string password="123456";

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

    string getPassword(){
        return password;
    }

    void setPassword(string password){
        this->password=password;
    }
};



#endif
