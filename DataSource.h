#pragma once

#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include "Department.h"
#include <vector>

using namespace std;

class DataSource
{
private:
	vector<Department> departments;
    vector<Appointment> appointments;

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
};



#endif
